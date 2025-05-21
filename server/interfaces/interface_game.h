#ifndef INTERFACE_GAME_H
#define INTERFACE_GAME_H

#include <memory>

#include "../../common/player_command_types.h"
#include "../../common/utility.h"

#include "interface_player_action.h"

class InterfacePlayerAction;

class InterfaceGameManager {
public:
    virtual ~InterfaceGameManager() = default;

    virtual void move(player_id_t player_id, MoveType move_type) = 0;
    virtual void reload(player_id_t player_id) = 0;
    virtual void shoot(player_id_t player_id, Position position, ammo_t ammo_count) = 0;
    virtual void plant_bomb(player_id_t player_id) = 0;
    virtual void defuse_bomb(player_id_t player_id) = 0;
    virtual void drop(player_id_t player_id) = 0;
    virtual void buy_ammo(player_id_t player_id, WeaponType weapon_type, ammo_t ammo_count) = 0;
    virtual void buy_weapon(player_id_t player_id, WeaponCode weapon_code) = 0;
    virtual void equip(player_id_t player_id, EquipType equip_type) = 0;
    virtual void process(std::unique_ptr<InterfacePlayerAction>& action) = 0;
};

#endif  // !INTERFACE_GAME_H
