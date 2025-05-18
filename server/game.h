#ifndef GAME_H
#define GAME_H

#include <string>

#include "../common/player_types.h"
#include "../common/utility.h"

class InterfaceGame {
public:
    virtual ~InterfaceGame() = default;

    virtual void move(player_id_t player_id, MoveType move_type) = 0;
    virtual void reload(player_id_t player_id) = 0;
    virtual void shoot(player_id_t player_id, Position position, ammo_t ammo_count) = 0;
    virtual void plant_bomb(player_id_t player_id) = 0;
    virtual void defuse_bomb(player_id_t player_id) = 0;
    virtual void drop(player_id_t player_id) = 0;
    virtual void buy_ammo(player_id_t player_id, WeaponType weapon_type, ammo_t ammo_count) = 0;
    virtual void buy_weapon(player_id_t player_id, WeaponCode weapon_code) = 0;
    virtual void equip(player_id_t player_id, EquipType equip_type) = 0;
};


class Game: public InterfaceGame {
private:
    std::string game_name;

public:
    Game(const std::string& game_name);
    ~Game();

    void start_game();
    void stop_game();
};

#endif  // !GAME_H
