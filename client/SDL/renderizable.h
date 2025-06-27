// Renderizable.h
#ifndef RENDERIZABLE_H
#define RENDERIZABLE_H

#include <SDL2/SDL.h>

class Renderizable {
public:
    virtual void draw(SDL_Renderer& renderer) = 0;
    virtual ~Renderizable() = default;
};

#endif
