#include "PlayersTypes.h"

/* COUNTER_TERRORIST */
PlayerImage CounterTerrorist::get_player_image() {
    return PlayerImage(id, Position(position.x, position.y), health, points);
}


/* TERRORIST */

// Aca posiblemente como en un futuro agregue el invitario, deba de indicar que el TT tiene la
// BOMBA!
PlayerImage Terrorist::get_player_image() {
    return PlayerImage(id, Position(position.x, position.y), health, points);
}
