#include "mapView.h"
MapView::MapView(const std::string& rute, Camera* camera_reseiver, ManageTexture* manejador,GameConfig& config):
        config(config),
        mapa(config.load_map(rute)),
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
}


void MapView::draw(SDL_Renderer& renderer) {

    for (size_t i = 0; i < mapa.size(); i++) {
        for (size_t j = 0; j < mapa[i].size(); j++) {
            SDL_Rect destRect = { static_cast<int>(j * config.get_tile_width()) - camera->getx(),
                                static_cast<int>(i * config.get_tile_height()) - camera->gety(),
                                config.get_tile_width(), config.get_tile_height()};

            char item = mapa[i][j];

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

MapView::~MapView() {  // Cierra SDL
}
