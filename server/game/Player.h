#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

#include <string>
#include <utility>
#include <vector>

#include "../../common/game_image.h"
#include "../../common/player_command_types.h"
#include "../../common/utility.h"
#include "../interfaces/interface_player_action.h"

#include "Equipement.h"
#include "ICanInteract.h"
#include "IGameZone.h"

class Player: public IPlayerAction, public ICanInteract {
public:
    Player(player_id_t id, Equipement&& equipement, IGameZone& game_zone,
           ISpawneableZone& spawneable_zone):
            id(id),
            equipement(std::move(equipement)),
            health(100),
            points(0),
            game_zone(game_zone),
            spawneable_zone(spawneable_zone) {}
    virtual ~Player() = default;
    void reset(bool full_reset);
    PlayerImage get_player_image(const Position& position);
    // Interface
    void damage(uint8_t damage) override;
    virtual void move(const MoveType& move_type) override;
    virtual void reload() override;
    // void equip(Weapon& weapon) override { equipement.primary = weapon;}
    virtual void shoot(const coordinate_t& mouse_x, const coordinate_t& mouse_y) override;

    /*
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
    IGameZone& game_zone;
    ISpawneableZone& spawneable_zone;
};

#endif  // GAME_PLAYER_H_
