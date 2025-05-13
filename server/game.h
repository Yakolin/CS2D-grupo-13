#ifndef GAME_H
#define GAME_H

class Game
{
public:
    Game();
    ~Game();
    void move_right(uint16_t player_id);
    void move_left(uint16_t player_id);
    void move_up(uint16_t player_id);
    void move_down(uint16_t player_id);
    void reload(uint16_t player_id, WeaponType weapon_type);
    void shoot(uint16_t player_id);
    void plant_bomb(uint16_t player_id);
    void defuse_bomb(uint16_t player_id);
    void drop_weapon(uint16_t player_id);
    void drop_bomb(uint16_t player_id);
    void buy_ammo(uint16_t player_id, WeaponType weapon_type, ammo_t ammo_count);
    void buy_weapon(uint16_t player_id, WeaponCode weapon_code);
};

#endif // !GAME_H