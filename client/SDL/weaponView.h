#ifndef WEAPONVIEW_H
#define WEAPONVIEW_H
#include <iostream>
#include "renderizable.h"


class WeaponView: public Renderizable {


public:
WeaponView() = default;


void draw(SDL_Renderer& renderer) override ;

// Método para actualizar el estado del arma
void update() ;

// Método para manejar la acción de disparar
void shoot();
};


#endif  // WEAPONVIEW_H