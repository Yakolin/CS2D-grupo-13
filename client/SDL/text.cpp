#include "text.h"
#include <stdexcept>


Text::Text(ManageTexture& manager, const TextView& id,const  int& x,const int& y): 
    manager(manager), 
    id(id), 
    current_text(""),
    x(x), 
    y(y)
    {}

void Text::updateText(const std::string& new_text, TTF_Font* font, SDL_Color color) {
    
    if (new_text != current_text) {
        current_text = new_text;
        manager.remove(id);
        manager.load_texture_text(id, font, color, current_text);
    }
}
void Text::draw(SDL_Renderer& renderer) {
    SDL_Texture* textura = manager.get_texture_text(id);
    if (!textura) return;
    SDL_Rect destino = manager.get_rect(id);  
    destino.x = x;
    destino.y = y; 
    SDL_RenderCopy(&renderer, textura, nullptr, &destino);
}

Text::~Text() {
}

