#include "SpecialWeapons.h"

#include <iostream>
void Bomb::set_on_bomb() {
    // Le aviso al timer que tiene que empezar a correr por ser yo la bomba
    timer.bomb_start();
    equiped = false;
    activate = true;
    std::cout << "Bomba activada" << std::endl;
}
void Bomb::set_equiped() { equiped = true; }
void Bomb::set_unequiped() { equiped = false; }
bool Bomb::is_equiped() { return equiped; }
bool Bomb::is_activate() { return activate; }
