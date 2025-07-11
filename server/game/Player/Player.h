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
#include "../Config/GameConfig.h"
#include "../Map/IDroppableZone.h"
#include "../Map/IGameZone.h"
#include "../Map/ISoundZone.h"

#include "Equipment.h"
#include "ICanInteract.h"
class Player: public IPlayerAction, public ICanInteract {

public:
    Player(player_id_t id, Team team, Skins skins, GameConfig::player_config_t& player_config,
           Equipment&& equipment, IGameZone& game_zone, ISoundZone& sound_zone):
            id(id),
            team(team),
            skins(skins),
            config(player_config),
            equipment(std::move(equipment)),
            health(player_config.health),
            deaths(0),
            kills(0),
            points(player_config.points),
            money(player_config.money),
            collected_money(player_config.money),
            mouse_position(0, 0),
            game_zone(game_zone),
            sound_zone(sound_zone) {}
    virtual ~Player() = default;
    bool dead();
    void reset(bool full_reset);
    void change_team(Team new_team) { team = new_team; }
    virtual Team get_team() override { return team; }
    PlayerImage get_player_image(const Position& position, SoundImage& sounds);

    // Interface
    virtual void damage(uint8_t damage) override;
    virtual bool is_dead() override;

    virtual bool equip(std::shared_ptr<IInteractuable>& droppable) override;
    virtual void move(const MoveType& move_type) override;
    virtual void reload() override;
    virtual void shoot(const coordinate_t& mouse_x, const coordinate_t& mouse_y) override;
    virtual void shoot_burst(const coordinate_t& mouse_x, const coordinate_t& mouse_y) override;
    virtual void defuse_bomb() override;
    // Buy
    virtual void buy_weapon(const WeaponCode& weapon_code) override;
    virtual void drop() override;
    virtual void change_weapon(const EquipType& equip_type) override;
    void give_money();
    virtual void give_points() override;
    virtual void watch(const coordinate_t& mouse_x, const coordinate_t& mouse_y) override;
    /*
     */
private:
    player_id_t id;
    Team team;
    Skins skins;
    GameConfig::player_config_t& config;
    Equipment equipment;
    health_t health;
    deaths_t deaths;
    deaths_t kills;
    points_t points;
    money_t money;
    money_t collected_money;
    Position mouse_position;
    IGameZone& game_zone;
    ISoundZone& sound_zone;

    void drop_on_dead();
};

#endif  // GAME_PLAYER_H_
