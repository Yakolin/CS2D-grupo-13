#include "text.h"
#include <stdexcept>


Text::Text(ManageTexture* manager, const Object& id,const  int& x,const int& y): 
    manager(manager), 
    id(id), 
    x(x), 
    y(y) 
    {}

void Text::draw(SDL_Renderer& renderer) {
    SDL_Texture* textura = manager->get_texture_text(id);
    if (!textura) return;

    SDL_Rect destino = manager->get_rect(id);   
    SDL_RenderCopy(&renderer, textura, nullptr, &destino);
}

Text::~Text() {
}

