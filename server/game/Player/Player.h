#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../../../common/game_image.h"
#include "../../../common/game_info.h"
#include "../../../common/player_command_types.h"
#include "../../../common/utility.h"
#include "../../interfaces/interface_player_action.h"
#include "../Map/IDroppableZone.h"
#include "../Map/IGameZone.h"

#include "Equipment.h"
#include "ICanInteract.h"
#include "player_config.h"

using points_t = uint16_t;
using multiplier_points_t = uint16_t;
using earned_points_t = uint16_t;

class Player: public IPlayerAction, public ICanInteract {
private:
    player_id_t id;
    Team team;
    Skins skins;
    Equipment equipment;
    health_t health;
    points_t points;
    money_t money;
    multiplier_points_t multiplier_points;
    Position mouse_position;
    IGameZone& game_zone;

    void drop_on_dead();

public:
    Player(player_id_t id, Team team, Skins skins, Equipment&& equipment, IGameZone& game_zone):
            id(id),
            team(team),
            skins(skins),
            equipment(std::move(equipment)),
            health(PlayerConfig::get_instance()["player"]["health"].as<health_t>),
            points(PlayerConfig::get_instance()["player"]["points"].as<points_t>),
            money(PlayerConfig::get_instance()["player"]["money"].as<money_t>),
            mouse_position(0, 0),
            game_zone(game_zone) {}
    virtual ~Player() = default;
    bool dead();
    void reset(bool full_reset);
    void change_team(Team new_team) { team = new_team; }
    virtual Team get_team() override { return team; }
    PlayerImage get_player_image(const Position& position);

    // Interface
    void damage(uint8_t damage) override;
    virtual bool is_dead() override;

    virtual bool equip(std::shared_ptr<IInteractuable>& droppable) override;
    virtual void move(const MoveType& move_type) override;
    virtual void reload() override;
    virtual void shoot(const ShootType& shoot_type, const coordinate_t& mouse_x,
                       const coordinate_t& mouse_y) override;
    virtual void defuse_bomb() override;
    // Buy
    virtual void buy_weapon(const WeaponCode& weapon_code) override;
    virtual void drop() override;
    virtual void change_weapon(const EquipType& equip_type) override;
    virtual void get_points() override;
    virtual void watch(const coordinate_t& mouse_x, const coordinate_t& mouse_y) override;
    /*
     */
};

#endif  // GAME_PLAYER_H_
