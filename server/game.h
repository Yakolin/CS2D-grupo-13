#ifndef GAME_H
#define GAME_H

class InterfaceGame {
public:
    virtual ~InterfaceGame() = default;

    virtual void move(uint16_t player_id, MoveType move_type) = 0;
    virtual void reload(uint16_t player_id, WeaponType weapon_type) = 0;
    virtual void shoot(uint16_t player_id, WeaponType weapon_type, ammo_t ammo_count) = 0;
    virtual void plant_bomb(uint16_t player_id) = 0;
    virtual void defuse_bomb(uint16_t player_id) = 0;
    virtual void drop_weapon(uint16_t player_id) = 0;
    virtual void drop_bomb(uint16_t player_id) = 0;
    virtual void buy_ammo(uint16_t player_id, WeaponType weapon_type, ammo_t ammo_count) = 0;
    virtual void buy_weapon(uint16_t player_id, WeaponCode weapon_code) = 0;
};

class Game: public InterfaceGame {
public:
    Game() = default;
    ~Game() = default;
};

#endif  // !GAME_H