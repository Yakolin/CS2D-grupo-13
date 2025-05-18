#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <arpa/inet.h>

#include "../../common/connection_closed_exception.h"
#include "../../common/game_image.h"
#include "../../common/lobby_types.h"
#include "../../common/player_types.h"
#include "../../common/socket.h"

class ClientProtocol {
private:
    Socket& socket;

    void read_byte_data(uint8_t& data);
    void read_two_byte_data(uint16_t& data);
    void read_player_image(GameImage& game_image);

    void send_byte_data(uint8_t& data);
    void send_two_byte_data(uint16_t& data);

public:
    ClientProtocol(Socket& socket);
    ~ClientProtocol();

    void send_lobby_command(LobbyCommandType command);
    void send_player_command(PlayerCommandType command);

    void send_create_game(const std::string& game_name);
    void send_join_game(const std::string& game_name);
    void send_list_games();

    void send_move(MoveType move_type);
    void send_buy_weapon(WeaponCode weapon_code);
    void send_buy_ammo(WeaponType weapon_type, ammo_t ammo_count);
    void send_reload(WeaponType weapon_type);
    void send_shoot(WeaponType weapon_type, ammo_t ammo_count);
    void send_plant_bomb();
    void send_defuse_bomb();
    void send_drop();

    player_id_t read_player_id();

    GameImage read_game_image();
};

#endif  // !1