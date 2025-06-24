#include "mapView.h"

#include <random>

#include "../../common/game_info.h"

const char TREE_AZTECT = 'F';
const char TREE_ENTRENAMIENTO = 'Z';
const char TREE_DESIERTO = 'M';

const char WALL_AZTECT = '#';
const char WALL_ENTRENAMIENTO = '?';
const char WALL_DESIERTO = '}';

const char BOX_AZTECT = '=';
const char BOX_ENTRENAMIENTO = '+';
const char BOX_DESIERTO = '-';

const char FLOOR_AZTECT = '.';
const char FLOOR_ENTRENAMIENTO = '_';
const char FLOOR_DESIERTO = ' ';
const int CANT_UMBRELLA = 3;


MapView::MapView(const MapInfo& info, Camera* camera_reseiver, ManageTexture* manejador,
                 GameConfig& config):
        config(config),
        mapa(completar_mapa(info)),
        width_map(mapa[0].size() * config.get_tile_width()),  // camara
        height_map(mapa.size() * config.get_tile_height()),   // camara
        camera(camera_reseiver),
        manejador(manejador),
        ids(),
        libres(),
        weapon_dropped(),
        zones(load_zones(info)) {

    ids[WALL_ENTRENAMIENTO] = Object::WALL_ENTRENAMIENTO;
    ids[WALL_AZTECT] = Object::WALL_AZTEC;
    ids[WALL_DESIERTO] = Object::WALL_DESIERTO;

    ids[FLOOR_DESIERTO] = Object::FLOOR_DESIERTO;            // piso del desierto
    ids[FLOOR_ENTRENAMIENTO] = Object::FLOOR_ENTRENAMIENTO;  // piso del entrenamiento
    ids[FLOOR_AZTECT] = Object::FLOOR_AZTEC;                 // piso azteca

    ids[TREE_AZTECT] = Object::TREE_AZTEC;
    ids[TREE_ENTRENAMIENTO] = Object::TREE_ENTRENAMIENTO;
    ids[TREE_DESIERTO] = Object::TREE_DESIERTO;

    ids[BOX_AZTECT] = Object::BOX2;
    ids[BOX_ENTRENAMIENTO] = Object::BOX4;
    ids[BOX_DESIERTO] = Object::BOX5;

}

void MapView::update_weapon_dropped(const std::vector<WeaponDropped>& dropped) {
    weapon_dropped.clear();
    for (const WeaponDropped& weaponDrop: dropped) {
        int x = weaponDrop.position.x * config.get_tile_width();
        int y = weaponDrop.position.y * config.get_tile_height();
        WeaponView weapon = WeaponView(*camera, *manejador, weaponDrop.weapon_code, x, y, 0.0f);
        this->weapon_dropped.push_back(weapon);
    }
}

void MapView::draw_weapon_dropped(SDL_Renderer& renderer) {
    for (WeaponView& weapon: this->weapon_dropped) {
        weapon.draw_dropped(renderer);
    }
}


void MapView::cargar_coordenadas(std::vector<std::vector<char>>& map,
                                 const std::vector<Position>& walls, const char& objet) {

    for (const Position& p: walls) map[p.y][p.x] = objet;
}

std::vector<std::vector<char>> MapView::completar_mapa(const MapInfo& info_map) {
    int max_fil = 0;
    int max_col = 0;
    for (const Position& p: info_map.walls) {
        if (p.y > max_fil)
            max_fil = p.y;
        if (p.x > max_col)
            max_col = p.x;
    }

    char piso = ' ', wall = ' ', box = ' ';

    switch (info_map.map_name) {
        case MapName::DESIERTO:
            piso = FLOOR_DESIERTO;
            wall = WALL_DESIERTO;
            box = BOX_DESIERTO;
            break;
        case MapName::PUEBLITO_AZTECA:
            piso = FLOOR_AZTECT;
            wall = WALL_AZTECT;
            box = BOX_AZTECT;
            break;
        case MapName::ZONA_ENTRENAMIENTO:
            piso = FLOOR_ENTRENAMIENTO;
            wall = WALL_ENTRENAMIENTO;
            box = BOX_ENTRENAMIENTO;
            break;
        default:
            break;
    }
    std::vector<std::vector<char>> mapa(max_fil + 1, std::vector<char>(max_col + 1, piso));
    cargar_coordenadas(mapa, info_map.walls, wall);
    cargar_coordenadas(mapa, info_map.boxes, box);
    return mapa;
}

void MapView::update_map_dimensions() {
    this->width_map = (mapa[0].size() * config.get_tile_width());
    this->height_map = (mapa.size() * config.get_tile_height());
}

void MapView::update_limites(Coordenada& pos_start, Coordenada& pos_end) {

    const int tileWidth = 32;
    const int tileHeight = 32;
    Coordenada cam;

    cam.x = camera->getX();
    cam.y = camera->getY();
    int camWidth = camera->getW();
    int camHeight = camera->getH();

    pos_start.x = cam.x / tileWidth;
    pos_start.y = cam.y / tileHeight;

    pos_end.x = (cam.x + camWidth) / tileWidth + 1;
    pos_end.y = (cam.y + camHeight) / tileHeight + 1;
    pos_end.x = std::min(static_cast<int>(pos_end.x), (int)mapa[0].size());
    pos_end.y = std::min(static_cast<int>(pos_end.y), (int)mapa.size());
}

void MapView::draw(SDL_Renderer& renderer) {

    Coordenada start;
    Coordenada end;
    update_limites(start, end);

    for (int row = start.y; row < end.y; ++row) {
        for (int col = start.x; col < end.x; ++col) {
            SDL_Rect destRect = {(col * config.get_tile_width()) - static_cast<int>(camera->getX()),
                                 (row * config.get_tile_width()) - static_cast<int>(camera->getY()),
                                 config.get_tile_width(), config.get_tile_height()};

            char item = mapa[row][col];
            auto it = ids.find(item);
            SDL_Texture* tex = manejador->get(it->second);
            SDL_RenderCopy(&renderer, tex, nullptr, &destRect);
        }
    }
}

void MapView::free_positions(const int& max_fil, const int& max_col, char piso) {
    for (int y = 0; y <= max_fil; ++y) {
        for (int x = 0; x <= max_col; ++x) {
            if (mapa[y][x] == piso) {
                this->libres.push_back(
                        Position{static_cast<coordinate_t>(x), static_cast<coordinate_t>(y)});
            }
        }
    }
}


TextureInfo MapView::load_zone_texture(const RectangleInfo& rectangle, const Object& zone,
                                       const SDL_Color& color) {

    int tile_width = config.get_tile_width();
    int tile_height = config.get_tile_height();
    int width = std::abs(rectangle.pos_max.x - rectangle.pos_min.x);
    int height = std::abs(rectangle.pos_max.y - rectangle.pos_min.y);
    SDL_Rect rect = {rect.x = std::min(rectangle.pos_min.x, rectangle.pos_max.x) * tile_width,
                     rect.y = std::min(rectangle.pos_min.y, rectangle.pos_max.y) * tile_height,
                     rect.w = width * tile_width, rect.h = height * tile_height};

    TextureInfo info;
    info.textura = manejador->create_texture_rect(rect, color, zone);
    info.medidas = rect;
    return info;
}

std::unordered_map<Object, TextureInfo> MapView::load_zones(const MapInfo& info) {
    std::unordered_map<Object, TextureInfo> map;

    map[Object::ZONE_BOMBA] = load_zone_texture(
            info.bomb_A, Object::ZONE_BOMBA, config.get_color_translucent(ColorTranslucent::ROJO));
    map[Object::ZONE_BOMBB] = load_zone_texture(
            info.bomb_B, Object::ZONE_BOMBB, config.get_color_translucent(ColorTranslucent::ROJO));
    map[Object::ZONE_COUNTERTERROSIT] =
            load_zone_texture(info.spawn_CT, Object::ZONE_COUNTERTERROSIT,
                              config.get_color_translucent(ColorTranslucent::AZUL));
    map[Object::ZONE_TERRORIST] =
            load_zone_texture(info.spawn_TT, Object::ZONE_TERRORIST,
                              config.get_color_translucent(ColorTranslucent::VERDE));
    return map;
}
void MapView::draw_zone(const Object& clave, SDL_Renderer& renderer) {

    const TextureInfo& info = zones.at(clave);
    SDL_Rect rect_b = info.medidas;
    rect_b.x -= static_cast<int>(camera->getX());
    rect_b.y -= static_cast<int>(camera->getY());
    SDL_RenderCopy(&renderer, info.textura, nullptr, &rect_b);
}

void MapView::draw_zones(SDL_Renderer& renderer) {

    draw_zone(Object::ZONE_BOMBA, renderer);
    draw_zone(Object::ZONE_BOMBB, renderer);
    draw_zone(Object::ZONE_COUNTERTERROSIT, renderer);
    draw_zone(Object::ZONE_TERRORIST, renderer);
}
int MapView::getMapWidth() { return width_map; }
int MapView::getMapHeight() { return height_map; }

MapView::~MapView() {}
