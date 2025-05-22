#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <memory>
#include <string>
#include <vector>

#include <arpa/inet.h>

#include "../common/connection_closed_exception.h"
#include "../common/game_image.h"
#include "../common/lobby_types.h"
#include "../common/player_command_types.h"
#include "../common/socket.h"
#include "../common/game_image.h"

#include "client_action.h"
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

    std::unique_ptr<Server::CreateGame> read_create_game(player_id_t player_id);
    std::unique_ptr<Server::JoinGame> read_join_game(player_id_t player_id);
    std::unique_ptr<Server::ListGames> read_list_games(player_id_t player_id);

    std::unique_ptr<Server::Move> read_move(player_id_t player_id);

    std::unique_ptr<Server::BuyWeapon> read_buy_weapon(player_id_t player_id);
    std::unique_ptr<Server::BuyAmmo> read_buy_ammo(player_id_t player_id);
    std::unique_ptr<Server::Reload> read_reload(player_id_t player_id);
    std::unique_ptr<Server::Shoot> read_shoot(player_id_t player_id);

    std::unique_ptr<Server::PlantBomb> read_plant_bomb(player_id_t player_id);
    std::unique_ptr<Server::DefuseBomb> read_defuse_bomb(player_id_t player_id);

    std::unique_ptr<Server::Drop> read_drop(player_id_t player_id);
    std::unique_ptr<Server::Equip> read_equip(player_id_t player_id);

    void send_player_id(player_id_t& player_id);

    void send_game_image(GameImage& game_image);
};

#endif  // !PROTOCOL_H
