#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "../common/connection_closed_exception.h"
#include "../common/player_types.h"
#include "../common/socket.h"
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

    std::unique_ptr<Move> read_move(player_id_t player_id);

    std::unique_ptr<BuyWeapon> read_buy_weapon(player_id_t player_id);

    std::unique_ptr<BuyAmmo> read_buy_ammo(player_id_t player_id);
    std::unique_ptr<Reload> read_reload(player_id_t player_id);
    std::unique_ptr<Shoot> read_shoot(player_id_t player_id);
    std::unique_ptr<DropWeapon> read_drop_weapon(player_id_t player_id);

    std::unique_ptr<PlantBomb> read_plant_bomb(player_id_t player_id);
    std::unique_ptr<DefuseBomb> read_defuse_bomb(player_id_t player_id);
    std::unique_ptr<DropBomb> read_drop_bomb(player_id_t player_id);
};

#endif // !PROTOCOL_H
