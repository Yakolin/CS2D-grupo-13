#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <memory>
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

#include "client_action.h"

namespace ServerSpace {
class Move;
class BuyWeapon;
class Shoot;
class ShootBurst;
class Equip;
class MousePosition;
/*
class BuyAmmo;
*/
}  // namespace ServerSpace


class ServerProtocol {
private:
    Socket& socket;
    void read_byte_data(uint8_t& data);
    void read_two_byte_data(uint16_t& data);

    const std::string read_string();

    void send_byte_data(const uint8_t& data);
    void send_two_byte_data(uint16_t& data);

    void send_map_info(const MapInfo& map_info);

    void send_position(const Position& position);

    void send_weapons(const PlayerImage& player_image);
    void send_common_sounds(const PlayerImage& player_image);
    void send_shoot_sounds(const PlayerImage& player_image);
    void send_sound(sound_type_t type, distance_sound_t distance);
    void send_sound_image(const PlayerImage& player_image);
    void send_client_id(player_id_t& player_id);
    void send_players_images(std::vector<PlayerImage>& players_images);
    void send_bullets_in_air(std::vector<BulletImage>& bullets_in_image);
    void send_bomb_image(BombImage& game_image);
    void send_weapons_dropped(std::vector<WeaponDropped>& weapons_dropped);
    void send_game_state_image(GameStateImage& game_state_image);


public:
    explicit ServerProtocol(Socket& socket);
    ~ServerProtocol();

    LobbyCommandType read_lobby_command();

    PlayerCommandType read_player_command();

    CreateGame read_create_game();

    JoinGame read_join_game();

    std::unique_ptr<ServerSpace::Move> read_move(const player_id_t& player_id);
    std::unique_ptr<ServerSpace::BuyWeapon> read_buy_weapon(const player_id_t& player_id);
    std::unique_ptr<ServerSpace::Shoot> read_shoot(const player_id_t& player_id);
    std::unique_ptr<ServerSpace::ShootBurst> read_shoot_burst(const player_id_t& player_id);

    std::unique_ptr<ServerSpace::Equip> read_equip(const player_id_t& player_id);
    /*
    std::unique_ptr<ServerSpace::BuyAmmo> read_buy_ammo(player_id_t player_id);

    */
    std::unique_ptr<ServerSpace::MousePosition> read_mouse_position(const player_id_t& player_id);

    Acknowledge read_acknowledge();

    void send_list_games(ListGame& games);

    void send_game_info(GameInfo& game_info);

    void send_game_image(GameImage& game_image);
};

#endif  // !PROTOCOL_H
