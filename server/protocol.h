#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "../common/connection_closed_exception.h"
#include "../common/socket.h"
#include "../common/player_types.h"
#include <memory>

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

    std::unique_ptr<PlayerAction> read_move(player_id_t player_id);
    /*

    BuyWeapon read_buy_weapon();
    BuyAmmo read_buy_ammo();
    Reload read_reload();
    Shoot read_shoot();
    DropWeapon read_drop_weapon();

    PlantBomb read_plant_bomb();
    DefuseBomb read_defuse_bomb();
    DropBomb read_drop_bomb();
    */
};

#endif // !PROTOCOL_H
