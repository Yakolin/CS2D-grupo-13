#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

#include <string>
#include <utility>
#include <vector>

#include "../../common/game_image.h"
#include "../../common/player_command_types.h"
#include "../../common/utility.h"
#include "../interfaces/interface_player_action.h"

#include "Equipment.h"
#include "ICanInteract.h"
#include "IDropeableZone.h"
#include "IGameZone.h"

class Player: public IPlayerAction, public ICanInteract {
public:
    Player(player_id_t id, Equipment&& equipment, IGameZone& game_zone):
            id(id), equipment(std::move(equipment)), health(100), points(0), game_zone(game_zone) {}
    virtual ~Player() = default;
    bool dead();
    void reset(bool full_reset);
    PlayerImage get_player_image(const Position& position, Team team);
    // Interface
    void damage(uint8_t damage) override;
    virtual void move(const MoveType& move_type) override;
    virtual void reload() override;
    virtual void shoot(const coordinate_t& mouse_x, const coordinate_t& mouse_y) override;
    virtual void buy_weapon(const WeaponCode& weapon_code) override;
    virtual void drop() override;
    virtual void equip(const EquipType& equip_type) override;

    /*
    virtual void defuse_bomb() override;
    */

protected:  // Por ahora lo dejamo asi
    player_id_t id;
    Equipment equipment;
    uint8_t health;
    uint8_t points;
    uint16_t money = 500;

private:
    IGameZone& game_zone;
};

#endif  // GAME_PLAYER_H_
