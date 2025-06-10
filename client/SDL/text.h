#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "../tipos.h"
#include "manageTexture.h"
#include "renderizable.h"
class Text : public Renderizable {
private:
    ManageTexture& manager;
    TextView id;
    std::string current_text;
    int x;
    int y;

public:
    explicit Text(ManageTexture& manager, const TextView& id,const  int& x,const int& y);

    void updateText(const std::string& new_text, TTF_Font* font, SDL_Color color);

    void draw(SDL_Renderer& renderer) override;

    ~Text();

};

#endif // TEXT_H
