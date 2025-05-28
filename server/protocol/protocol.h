#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <memory>
#include <string>
#include <vector>

#include <arpa/inet.h>

#include "../../common/connection_closed_exception.h"
#include "../../common/game_image.h"
#include "../../common/lobby_types.h"
#include "../../common/player_command_types.h"
#include "../../common/socket.h"

#include "client_action.h"

namespace ServerSpace {
class Move;
/*
class CreateGame;
class JoinGame;
class BuyWeapon;
class BuyAmmo;
class Shoot;
class Equip;
*/
}  // namespace ServerSpace


class ServerProtocol {
private:
    Socket& socket;
    void read_byte_data(uint8_t& data);
    void read_two_byte_data(uint16_t& data);

    const std::string read_game_name();

    void send_byte_data(uint8_t& data);
    void send_two_byte_data(uint16_t& data);

    void send_player_image(GameImage& game_image);

public:
    ServerProtocol(Socket& socket);
    ~ServerProtocol();

    LobbyCommandType read_lobby_command();

    PlayerCommandType read_player_command();

    std::string read_create_game();
    std::string read_join_game();

    std::unique_ptr<ServerSpace::Move> read_move(player_id_t player_id);
    /*
    std::unique_ptr<ServerSpace::BuyWeapon> read_buy_weapon(player_id_t player_id);
    std::unique_ptr<ServerSpace::BuyAmmo> read_buy_ammo(player_id_t player_id);
    std::unique_ptr<ServerSpace::Shoot> read_shoot(player_id_t player_id);

    std::unique_ptr<ServerSpace::Equip> read_equip(player_id_t player_id);
    */

    void send_list_games(std::vector<std::string>& list_games);

    void send_game_image(GameImage& game_image);
};

#endif  // !PROTOCOL_H