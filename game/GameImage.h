#ifndef GAME_IMAGE_H_
#define GAME_IMAGE_H_
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include "Type.h"

class GameImage {
    public:
    void add_player_state(TypesStates::PlayerState&& state) {players.push_back(std::move(state));}
    void add_object_state(TypesStates::ObjectState&& state) {objects.push_back(std::move(state));}
    
    // Hace falta una forma de adquirir esos players y objets
    private:
    std::vector<TypesStates::PlayerState> players;
    std::vector<TypesStates::ObjectState> objects;
};


#endif // GAME_IMAGE_H_