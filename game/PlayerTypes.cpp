#include "PlayersTypes.h"

/* COUNTER_TERRORIST */
PlayerImage CounterTerrorist::get_player_image() {
    return PlayerImage(id, Position(position.x, position.y), health, points);
}


/* TERRORIST */

// Aca posiblemente como en un futuro agregue el invitario, deba de indicar que el TT tiene la
// BOMBA!
void Terrorist::plant_bomb() {
    // Si el arma actual es la bomba entonces si podes llamar a fire
}
PlayerImage Terrorist::get_player_image() {
    return PlayerImage(id, Position(position.x, position.y), health, points);
}
