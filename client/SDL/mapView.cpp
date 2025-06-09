#include "mapView.h"
MapView::MapView(const std::vector<Position> walls, Camera* camera_reseiver, ManageTexture* manejador,GameConfig& config):
        config(config),
        mapa(cargar_coordenadas(walls)),
        width_map(mapa[0].size() * config.get_tile_width()),  // camara
        height_map(mapa.size() * config.get_tile_height()),    // camara
        camera(camera_reseiver),
        manejador(manejador),
        ids() {
    ids['#'] = Object::WALL;
    ids[' '] = Object::STONE;
    ids['~'] = Object::WATER;
    ids['='] = Object::BOX;
    ids['.'] = Object::GRASS;
    ids['A'] = Object::ZONE_BOMBA2;
    ids['B'] = Object::ZONE_BOMBA1;
    ids['T'] = Object::ZONE_TERRORIST;
    ids['C'] = Object::ZONE_COUNTERTERROSIT;
}


std::vector<std::vector<char>>  MapView::cargar_coordenadas(const std::vector<Position> walls ) {

    int max_fila = 0;
    int max_columna = 0;
    for (const Position& p : walls) {
        if (p.y > max_fila) max_fila = p.y;
        if (p.x > max_columna) max_columna = p.x;
    }
    std::vector<std::vector<char>> mapa(max_fila + 1, std::vector<char>(max_columna + 1, '.'));
    for (const Position& p : walls) {
        mapa[p.y][p.x] = '#';
    }

    return mapa;
}

void MapView::update_map_dimensions() {
    this->width_map = (mapa[0].size() * config.get_tile_width());
    this->height_map = (mapa.size() * config.get_tile_height());
}

void MapView::update_limites(Coordenada& pos_start,Coordenada& pos_end){

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

    // Asegurarse de no pasarse del tamaño del mapa
    pos_end.x = std::min(static_cast<int>(pos_end.x), (int)mapa[0].size());
    pos_end.y = std::min(static_cast<int>(pos_end.y), (int)mapa.size());
}

void MapView::draw(SDL_Renderer& renderer) {

    Coordenada start;
    Coordenada end;
    update_limites(start,end);

    for (int row = start.y; row < end.y; ++row) {
        for (int col = start.x; col < end.x; ++col) {
            SDL_Rect destRect = { (col * config.get_tile_width()) - static_cast<int>(camera->getX()), 
                                (row * config.get_tile_width()) - static_cast<int>(camera->getY()), 
                                config.get_tile_width(), config.get_tile_height()};

            char item = mapa[row][col];

            auto it = ids.find(item);
            if (it != ids.end()) {
                SDL_Texture* tex = manejador->get(it->second);
                SDL_RenderCopy(&renderer, tex, nullptr, &destRect);
            }
        }
    }

}


int MapView::getMapWidth() { return width_map; }
int MapView::getMapHeight() { return height_map; }

MapView::~MapView() { 
}
