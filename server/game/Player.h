#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

#include <memory>
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
    Player(player_id_t id, Team team, Equipment&& equipment, IGameZone& game_zone):
            id(id),
            team(team),
            equipment(std::move(equipment)),
            health(5),
            points(0),
            game_zone(game_zone) {}

    ~Player() = default;
    void reset(bool full_reset);
    void change_team(Team new_team) { team = new_team; }
    virtual Team get_team() override { return team; }
    PlayerImage get_player_image(const Position& position);

    // Interface
    void damage(uint8_t damage) override;
    virtual bool is_dead() override;

    virtual void equip_bomb(std::weak_ptr<Bomb> bomb) override;
    virtual bool equip_weapon(std::shared_ptr<Weapon>& weapon) override;

    virtual void move(const MoveType& move_type) override;
    virtual void reload() override;
    virtual void shoot(const coordinate_t& mouse_x, const coordinate_t& mouse_y) override;
    // Buy
    virtual void buy_weapon(const WeaponCode& weapon_code) override;
    virtual void drop() override;
    virtual void equip(const EquipType& equip_type) override;
    virtual void get_points(uint8_t new_points) override;
    /*
    virtual void defuse_bomb() override;
    */
private:
    player_id_t id;
    Team team;
    Equipment equipment;
    uint8_t health;
    uint8_t points;
    uint16_t money = 5000;
    IGameZone& game_zone;
};

#endif  // GAME_PLAYER_H_
