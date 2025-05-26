#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

#include <string>
#include <utility>
#include <vector>

#include "../../common/game_image.h"
#include "../../common/player_command_types.h"
#include "../../common/utility.h"
#include "../interfaces/interface_player_action.h"
#include "GameZone.h"
#include "Equipement.h"
#include "Map.h"

class Player: public IPlayerAction {
public:
    Player(player_id_t id, GameZone& game_zone): id(id),health(100), points(0), game_zone(game_zone) {}
    virtual ~Player() = default;
    void reset();
    void get_damage(uint8_t damage);
    virtual PlayerImage get_player_image(Position& position) = 0;
    virtual void move(const MoveType& move_type) override;
    virtual void reload() override {}

    /*
    virtual void shoot(const coordinate_t& mouse_x, const coordinate_t& mouse_y) override;
    virtual void plant_bomb() override;
    virtual void defuse_bomb() override;
    virtual void drop() override;
    virtual void buy_ammo(const WeaponType& weapon_type, const ammo_t& ammo_count) override;
    virtual void buy_weapon(const WeaponCode& weapon_code) override;
    virtual void equip(const EquipType& equip_type) override;
    */

protected:  // Por ahora lo dejamo asi
    player_id_t id;
    Equipement equipement;
    uint8_t health;
    uint8_t points;
private: 
    GameZone& game_zone;
};

#endif  // GAME_PLAYER_H_
