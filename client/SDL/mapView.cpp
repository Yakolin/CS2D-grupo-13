#include "mapView.h"
#include "../../common/game_info.h"
#include <random>

const char  TREE_AZTECT ='F';
const char  TREE_ENTRENAMIENTO ='Z';
const char  TREE_DESIERTO ='M';
const char  WALL_AZTECT ='#';
const char  WALL_ENTRENAMIENTO ='#';
const char  WALL_DESIERTO ='#';
const char  FLOOR_AZTECT ='.';
const char  FLOOR_ENTRENAMIENTO ='_';
const char  FLOOR_DESIERTO =' ';


MapView::MapView(const MapInfo& info, Camera* camera_reseiver,
                 ManageTexture* manejador, GameConfig& config):
        config(config),
        mapa(completar_mapa(info)),
        width_map(mapa[0].size() * config.get_tile_width()),  // camara
        height_map(mapa.size() * config.get_tile_height()),   // camara
        camera(camera_reseiver),
        manejador(manejador),
        ids(),
        libres(),
        weapon_dropped()
        { 
    ids['~'] = Object::WATER;
    ids['='] = Object::BOX;
    ids['A'] = Object::ZONE_BOMBA2;
    ids['B'] = Object::ZONE_BOMBA1;
    ids['T'] = Object::ZONE_TERRORIST;
    ids['C'] = Object::ZONE_COUNTERTERROSIT;

    ids[WALL_ENTRENAMIENTO] = Object::WALL_ENTRENAMIENTO;
    ids[WALL_AZTECT] = Object::WALL_AZTEC;
    ids[WALL_DESIERTO] = Object::WALL_DESIERTO;

    ids[FLOOR_DESIERTO] = Object::FLOOR_DESIERTO;        // piso del desierto
    ids[FLOOR_ENTRENAMIENTO] = Object::FLOOR_ENTRENAMIENTO;   // piso del entrenamiento
    ids[FLOOR_AZTECT] = Object::FLOOR_AZTEC;           // piso azteca

    ids['='] = Object::BOX;
    ids['~'] = Object::WATER;

    ids['A'] = Object::ZONE_BOMBA2;
    ids['B'] = Object::ZONE_BOMBA1;
    ids['T'] = Object::ZONE_TERRORIST;
    ids['C'] = Object::ZONE_COUNTERTERROSIT;

    // Árboles según mapa
    ids[TREE_AZTECT] = Object::TREE_AZTEC;
    ids[TREE_ENTRENAMIENTO] = Object::TREE_ENTRENAMIENTO;
    ids[TREE_DESIERTO] = Object::TREE_DESIERTO;
}

void MapView::update_weapon_dropped( const std::vector<WeaponDropped>& dropped){
    weapon_dropped.clear();
    for (const WeaponDropped& weaponDrop: dropped) {
        int x = weaponDrop.position.x * config.get_tile_width();
        int y = weaponDrop.position.y * config.get_tile_height();
        WeaponView weapon = WeaponView(*camera,*manejador, weaponDrop.weapon_code, x,y,0.0f);
        this->weapon_dropped.push_back(weapon);
    }
}
std::vector<std::vector<char>> MapView::cargar_coordenadas(const std::vector<Position> walls, const char& piso, const int& max_fil, const int& max_col, const char& objet) {

    std::vector<std::vector<char>> mapa(max_fil + 1, std::vector<char>(max_col + 1, piso));
    for (const Position& p: walls) {
        mapa[p.y][p.x] = objet;
    }

    return mapa;
}
void  MapView::draw_weapon_dropped(SDL_Renderer& renderer){
    for ( WeaponView& weapon: this->weapon_dropped) {
        weapon.draw_dropped(renderer);
    }
}


/*
void MapView::free_positions( std::vector<std::vector<char>> mapa, const char& piso,const char& wall, const int& max_fil, const int& max_col){
    for (int y = 0; y <= max_fil; ++y) {
        for (int x = 0; x <= max_col; ++x) {
            if (mapa[y][x] == piso && mapa[y][x] == wall) {
                this->libres.push_back(Position{static_cast<coordinate_t>(x), static_cast<coordinate_t>(y)});
 
            }
        }
    }
}*/
void MapView::load_trees(int& size_objet) {
    size_objet = std::min(size_objet, static_cast<int>(this->libres.size()));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(this->libres.begin(), this->libres.end(), gen);

}
std::vector<std::vector<char>> MapView::completar_mapa(const MapInfo& info_map){
    int max_fil = 0;
    int max_col = 0;
    for (const Position& p: info_map.walls) {
        if (p.y > max_fil)
            max_fil = p.y;
        if (p.x > max_col)
            max_col = p.x;
    }

    char piso = ' ', wall = ' ';

    switch (info_map.map_name){
        case MapName::DESIERTO:
            piso = FLOOR_DESIERTO;
            wall = WALL_DESIERTO;
            break;
        case MapName::PUEBLITO_AZTECA:
            piso = FLOOR_AZTECT;
            wall = WALL_AZTECT;

            break;
        case MapName::ZONA_ENTRENAMIENTO:
            piso = FLOOR_ENTRENAMIENTO;
            wall = WALL_ENTRENAMIENTO;

            break;
        default:
            break;
    }
    std::vector<std::vector<char>> mapa = cargar_coordenadas(info_map.walls, piso, max_fil, max_col,wall);
    //free_positions(mapa, piso, wall,max_fil, max_col);
    //int cantidad_arboles = 5; //todo podria ser configurable
   // load_trees(cantidad_arboles);

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
            if (it != ids.end() && item != TREE_AZTECT && item != TREE_ENTRENAMIENTO && item != TREE_DESIERTO) {
                SDL_Texture* tex = manejador->get(it->second);
                SDL_RenderCopy(&renderer, tex, nullptr, &destRect);
            }
        }
    }
}

void MapView::render_objet(SDL_Renderer& renderer){
    MapName map = MapName::PUEBLITO_AZTECA;
    char objet= TREE_AZTECT;

    for (size_t i = 0; i < 5 && i < libres.size(); i++) {
        Position p = libres.at(i); 
        SDL_Rect destRect = {
            (p.x * config.get_tile_width()) - static_cast<int>(camera->getX()),
            (p.y * config.get_tile_height()) - static_cast<int>(camera->getY()),
            config.get_tile_width()*3,
            config.get_tile_height()*3
        };

        switch (map) {
            case MapName::DESIERTO:
                objet = TREE_DESIERTO;
                break;
            case MapName::PUEBLITO_AZTECA:
                objet = TREE_AZTECT;
                break;
            case MapName::ZONA_ENTRENAMIENTO:
                objet = TREE_ENTRENAMIENTO;
                break;
            default:
                break;
        }

        auto it = ids.find(objet);
        if (it != ids.end()) {
            SDL_Texture* tex = manejador->get(it->second);
            SDL_RenderCopy(&renderer, tex, nullptr, &destRect);
        }
    }


}
int MapView::getMapWidth() { return width_map; }
int MapView::getMapHeight() { return height_map; }

MapView::~MapView() {}
