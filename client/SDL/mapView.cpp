#include "mapView.h"
MapView::MapView(const std::vector<std::vector<char>>& mapa_recibido, const int& width_reseiver,
                 const int& height_reseiver, Camera* camera_reseiver, ManageTexture* manejador):
        width(width_reseiver),    // medidas de la ventana
        height(height_reseiver),  // ¿medidas de la ventana
        mapa(mapa_recibido),
        width_map(mapa_recibido[0].size() * 32),  // camara
        height_map(mapa_recibido.size() * 32),    // camara
        camera(camera_reseiver),
        manejador(manejador),
        ids() {
    ids['#'] = Objet::WALL;
    ids[' '] = Objet::STONE;
    ids['~'] = Objet::WATER;
    ids['='] = Objet::BOX;
    ids['.'] = Objet::GRASS;
}


void MapView::draw(SDL_Renderer& renderer) {

    for (size_t i = 0; i < mapa.size(); i++) {
        for (size_t j = 0; j < mapa[i].size(); j++) {
            SDL_Rect destRect = {
            static_cast<int>(j * 32) - camera->getx(),
            static_cast<int>(i * 32) - camera->gety(),
            32, 32
        };

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
