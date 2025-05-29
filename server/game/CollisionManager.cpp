#include "CollisionManager.h"

#include <iostream>

bool CollisionManager::valid_movement(const Position& actual_position,
                                      const Position& next_position) {
    Position destino = actual_position + next_position;
    // Aca los destinos son distintos porque la matriz esta "invertida" con respecto a los vectores
    int x = destino.x;
    int y = destino.y;
    return walls[y][x] != Wall;
}
