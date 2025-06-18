#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#include <vector>

#include <arpa/inet.h>

#include "../../common/connection_closed_exception.h"
#include "../../common/game_image.h"
#include "../../common/game_info.h"
#include "../../common/lobby_action.h"
#include "../../common/lobby_types.h"
#include "../../common/player_command_types.h"
#include "../../common/socket.h"
#include "../../common/utility.h"

class ClientProtocol {
private:
    Socket& socket;

    void read_byte_data(uint8_t& data);
    void read_two_byte_data(uint16_t& data);

    void read_map_info(MapInfo& map_info);

    void read_client_id(player_id_t& player_id);
    void read_position(Position& position);
    void read_weapons(std::vector<WeaponImage>& weapons);
    void read_player_image(std::vector<PlayerImage>& players_image);
    void read_bullets_in_air(std::vector<BulletImage>& bullets_in_air);
    void read_bomb(BombImage& game_image);
    void read_weapons_dropped(std::vector<WeaponDropped>& weapons_dropped);
    void read_game_state_image(GameStateImage& game_state_image);

    void send_byte_data(uint8_t& data);
    void send_two_byte_data(uint16_t& data);

    void send_string(std::string& string);
    void send_common_shoot(player_command_t& shoot_command, coordinate_t& mouse_x,
                           coordinate_t& mouse_y);

public:
    explicit ClientProtocol(Socket& socket);
    ~ClientProtocol();

    void send_lobby_command(LobbyCommandType command);
    void send_player_command(PlayerCommandType command);

    void send_create_game(const CreateGame& create_game);
    void send_join_game(const JoinGame& join_game);
    void send_list_games();

    void send_move(MoveType& move_type);
    void send_buy_weapon(WeaponCode& weapon_code);
    void send_buy_ammo(WeaponType& weapon_type, ammo_t& ammo_count);
    void send_reload();
    void send_shoot(coordinate_t& mouse_x, coordinate_t& mouse_y);
    void send_burst_shoot(coordinate_t& mouse_x, coordinate_t& mouse_y);
    void send_plant_bomb();
    void send_defuse_bomb();
    void send_drop();
    void send_equip(EquipType& equip_type);
    void send_mouse_position(coordinate_t& mouse_x, coordinate_t& mouse_y);

    GameInfo read_game_info();
    void send_acknowledge(Acknowledge& ack);
    std::vector<std::string> read_list_games();
    GameImage read_game_image();
};

#endif  // !1