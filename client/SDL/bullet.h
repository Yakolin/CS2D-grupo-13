
#ifndef BULLET_H
#define BULLET_H
#include "../tipos.h"

#include "renderizable.h"


class Bullet: public Renderizable {
private:
    Coordenada current;  // Posición actual de la bala
    Coordenada end;      // Destino de la bala
    Coordenada camera;
    SDL_Texture* texture;
    Uint32 start_time;
    Uint32 end_time = 50;  // Aca es en ms

public:
    Bullet(const Coordenada& start, const Coordenada& end, SDL_Texture* texture);

    void draw(SDL_Renderer& renderer) override;

    float get_currentX();
    float get_currenty();

    float get_endX();

    float get_endy();

    bool finalizado();
    void set_camera(const Coordenada& camera) { this->camera = camera; }
    // Saber si la bala llegó a su destino
    bool has_reached_destination(float speed = 10.0f) const;
};
#endif  // BULLET_H