#ifndef MOCK_PLAYER_H
#define MOCK_PLAYER_H

#include <gmock/gmock.h>

#include "../../common/player_command_types.h"
#include "../../common/utility.h"
#include "../../server/interfaces/interface_player_action.h"

class MockPlayer: public IPlayerAction {
public:
    MOCK_METHOD(void, move, (const MoveType& move_type), (override));
    MOCK_METHOD(void, reload, (), (override));
    MOCK_METHOD(void, shoot, (const coordinate_t& mouse_x, const coordinate_t& mouse_y),
                (override));
    MOCK_METHOD(void, plant_bomb, (), (override));
    MOCK_METHOD(void, defuse_bomb, (), (override));
    MOCK_METHOD(void, drop, (), (override));
    MOCK_METHOD(void, buy_ammo, (const WeaponType& weapon_type, const ammo_t& ammo_count),
                (override));
    MOCK_METHOD(void, buy_weapon, (const WeaponCode& weapon_code), (override));
    MOCK_METHOD(void, equip, (const EquipType& equip_type), (override));
};

#endif  // MOCK_PLAYER_H
