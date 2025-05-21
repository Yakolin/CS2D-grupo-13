#ifndef MOCK_GAME_H
#define MOCK_GAME_H

#include <gmock/gmock.h>

#include "../../common/player_command_types.h"
#include "../../common/utility.h"
#include "../../server/game.h"

class MockGame: public InterfaceGameManager {
public:
    MOCK_METHOD(void, move, (player_id_t player_id, MoveType move_type), (override));
    MOCK_METHOD(void, reload, (player_id_t player_id), (override));
    MOCK_METHOD(void, shoot, (player_id_t player_id, Position position, ammo_t ammo_count),
                (override));
    MOCK_METHOD(void, plant_bomb, (player_id_t player_id), (override));
    MOCK_METHOD(void, defuse_bomb, (player_id_t player_id), (override));
    MOCK_METHOD(void, drop, (player_id_t player_id), (override));
    MOCK_METHOD(void, buy_ammo, (player_id_t player_id, WeaponType weapon_type, ammo_t ammo_count),
                (override));
    MOCK_METHOD(void, buy_weapon, (player_id_t player_id, WeaponCode weapon_code), (override));
    MOCK_METHOD(void, equip, (player_id_t player_id, EquipType equip_type), (override));
    MOCK_METHOD(void, process, (std::unique_ptr<InterfacePlayerAction> & action), (override));
};

#endif  // MOCK_GAME_H