
#ifndef BULLET_H
#define BULLET_H
#include "../tipos.h"

#include "renderizable.h"


class Bullet: public Renderizable {
private:
    Coordenada current;  // Posición actual de la bala
    Coordenada end;      // Destino de la bala
    Coordenada camera;
    int width;
    WeaponCode code;
    Uint32 start_time;
    Uint32 end_time = 50;  // Aca es en ms

    SDL_Texture* crear_cono(SDL_Renderer* renderer, SDL_Point p_inicial, SDL_Point p_final,
                            double apertura_grados, int paso);

public:
    Bullet(const Coordenada& start, const Coordenada& end, const int& width,
           const WeaponCode& code);

    void calculate_values(SDL_Rect& destination_rect, double& angulo, SDL_Point& center,
                          const SDL_Point& p_init, const SDL_Point& p_end);

    void draw(SDL_Renderer& renderer, SDL_Texture* texture, SDL_Rect destination_rect,
              double angulo, SDL_Point center);

    void draw(SDL_Renderer& renderer) override;

    float get_currentX();

    float get_currenty();

    float get_endX();

    float get_endy();

    bool finalizado();

    void set_camera(const Coordenada& camera) { this->camera = camera; }
};
#endif  // BULLET_H
