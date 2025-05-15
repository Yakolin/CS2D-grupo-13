#include "Player.h"
//  "Copyright 2025 Yaco Santamarina"
void Player::move(Vector2&& direction) { position += direction; }

// void Player::fire_weapon_equiped() { equipement.current_weapon->fire(); }

// void Player::change_weapon_equiped() {}

TypesStates::player_state_t Player::player_info() {
    TypesStates::player_state_t state;
    state.id = id;
    state.health = health;
    state.position_x = position.x;
    state.position_y = position.y;
    state.alive = health > 0;
    return state;
}
