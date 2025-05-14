#ifndef MOCK_GAME_H
#define MOCK_GAME_H

#include <gmock/gmock.h>
#include "../../server/game.h"
#include "../../common/player_types.h"

class MockGame : public InterfaceGame
{
public:
    MOCK_METHOD(void, move, (uint16_t player_id, MoveType move_type), (override));
    MOCK_METHOD(void, reload, (uint16_t player_id, WeaponType weapon_type), (override));
    MOCK_METHOD(void, shoot, (uint16_t player_id, WeaponType weapon_type, ammo_t ammo_count), (override));
    MOCK_METHOD(void, plant_bomb, (uint16_t player_id), (override));
    MOCK_METHOD(void, defuse_bomb, (uint16_t player_id), (override));
    MOCK_METHOD(void, drop_weapon, (uint16_t player_id), (override));
    MOCK_METHOD(void, drop_bomb, (uint16_t player_id), (override));
    MOCK_METHOD(void, buy_ammo, (uint16_t player_id, WeaponType weapon_type, ammo_t ammo_count), (override));
    MOCK_METHOD(void, buy_weapon, (uint16_t player_id, WeaponCode weapon_code), (override));
};

#endif // MOCK_GAME_H