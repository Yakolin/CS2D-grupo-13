#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "common/connection_closed_exception.h"
#include "common/socket.h"
#include "common/player_types.h"

#include "player_action.h"

class ServerProtocol
{
private:
    Socket &socket;
    void read_byte_data(uint8_t &data);

public:
    ServerProtocol(Socket &socket);
    ~ServerProtocol();

    PlayerCommandType read_player_command();

    MoveRight read_move_right();
    MoveLeft read_move_left();
    MoveUp read_move_up();
    MoveDown read_move_down();

    BuyWeapon read_buy_weapon();
    BuyAmmo read_buy_ammo();
    Reload read_reload();
    Shoot read_shoot();
    DropWeapon read_drop_weapon();

    PlantBomb read_plant_bomb();
    DefuseBomb read_defuse_bomb();
    DropBomb read_drop_bomb();
};

#endif // !PROTOCOL_H
