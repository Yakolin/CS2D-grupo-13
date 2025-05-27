#include "protocol.h"

using ServerSpace::Move;
/*
using ServerSpace::BuyAmmo;
using ServerSpace::BuyWeapon;
using ServerSpace::Equip;
using ServerSpace::Shoot;
*/

ServerProtocol::ServerProtocol(Socket& socket): socket(socket) {}

ServerProtocol::~ServerProtocol() {}

void ServerProtocol::read_byte_data(uint8_t& data) {
    uint8_t data_readed;
    this->socket.recvall(&data_readed, sizeof(uint8_t));
    if (this->socket.is_stream_recv_closed()) {
        throw ConnectionClosedException("El cliente cerró la conexión");
    }
    data = data_readed;
}

void ServerProtocol::read_two_byte_data(uint16_t& data) {
    uint16_t data_readed;
    this->socket.recvall(&data_readed, sizeof(uint16_t));
    if (this->socket.is_stream_recv_closed()) {
        throw ConnectionClosedException("El cliente cerró la conexión");
    }
    data = ntohs(data_readed);
}

const std::string ServerProtocol::read_game_name() {
    std::string game_name;
    length_name_t name_length;
    this->socket.recvall(reinterpret_cast<char*>(&name_length), sizeof(name_length));
    if (this->socket.is_stream_recv_closed()) {
        throw ConnectionClosedException("Error al intentar leer datos del cliente");
    }
    length_name_t length = ntohs(name_length);
    std::vector<char> nameGameBuffer(length);
    this->socket.recvall(nameGameBuffer.data(), length);
    if (this->socket.is_stream_recv_closed()) {
        throw ConnectionClosedException("Error al intentar leer datos del cliente");
    }
    game_name.assign(nameGameBuffer.begin(), nameGameBuffer.end());
    return game_name;
}

LobbyCommandType ServerProtocol::read_lobby_command() {
    lobby_command_t command;
    this->read_byte_data(command);
    return static_cast<LobbyCommandType>(command);
}

std::string ServerProtocol::read_create_game() { return this->read_game_name(); }

std::string ServerProtocol::read_join_game() { return this->read_game_name(); }

PlayerCommandType ServerProtocol::read_player_command() {
    player_command_t command;
    this->read_byte_data(command);
    return static_cast<PlayerCommandType>(command);
}

std::unique_ptr<Move> ServerProtocol::read_move(player_id_t player_id) {
    move_t move_type;
    this->read_byte_data(move_type);
    return std::make_unique<Move>(player_id, static_cast<MoveType>(move_type));
}

/*

std::unique_ptr<BuyWeapon> ServerProtocol::read_buy_weapon(player_id_t player_id) {
    weapon_code_t weapon_code;
    this->read_byte_data(weapon_code);
    return std::make_unique<BuyWeapon>(player_id, static_cast<WeaponCode>(weapon_code));
}

std::unique_ptr<BuyAmmo> ServerProtocol::read_buy_ammo(player_id_t player_id) {
    weapon_type_t weapon_type;
    ammo_t ammo_count;
    this->read_byte_data(weapon_type);
    this->read_two_byte_data(ammo_count);
    return std::make_unique<BuyAmmo>(player_id, static_cast<WeaponType>(weapon_type), ammo_count);
}

std::unique_ptr<Shoot> ServerProtocol::read_shoot(player_id_t player_id) {
    coordinate_t x;
    coordinate_t y;
    this->read_two_byte_data(x);
    this->read_two_byte_data(y);
    return std::make_unique<Shoot>(player_id, x, y);
}

std::unique_ptr<Equip> ServerProtocol::read_equip(player_id_t player_id) {
    equip_type_t equip_type;
    this->read_byte_data(equip_type);
    return std::make_unique<Equip>(player_id, static_cast<EquipType>(equip_type));
}
*/
void ServerProtocol::send_byte_data(uint8_t& data) {
    this->socket.sendall(&data, sizeof(uint8_t));
    if (this->socket.is_stream_send_closed()) {
        throw ConnectionClosedException("Error al intentar enviar datos al cliente");
    }
}

void ServerProtocol::send_two_byte_data(uint16_t& data) {
    uint16_t data_to_send = htons(data);
    this->socket.sendall(&data_to_send, sizeof(uint16_t));
    if (this->socket.is_stream_send_closed()) {
        throw ConnectionClosedException("Error al intentar enviar datos al cliente");
    }
}

void ServerProtocol::send_list_games(std::vector<std::string>& list_games) {
    length_games_list_t list_size = list_games.size();
    this->send_two_byte_data(list_size);

    for (const std::string& game_name: list_games) {
        length_name_t name_length = game_name.size();
        this->send_two_byte_data(name_length);

        this->socket.sendall(game_name.data(), name_length);
        if (this->socket.is_stream_send_closed()) {
            throw ConnectionClosedException("Error al intentar enviar datos al cliente");
        }
    }
}

void ServerProtocol::send_player_image(GameImage& game_image) {

    std::vector<PlayerImage> players_images = game_image.players_images;
    length_players_images_t length_players = players_images.size();
    this->send_two_byte_data(length_players);

    for (const PlayerImage& player_image: players_images) {
        player_id_t player_id = player_image.player_id;
        this->send_two_byte_data(player_id);

        coordinate_t x = player_image.position.x;
        this->send_two_byte_data(x);

        coordinate_t y = player_image.position.y;
        this->send_two_byte_data(y);

        health_t health = player_image.health;
        this->send_byte_data(health);

        points_t points = player_image.points;
        this->send_byte_data(points);
    }
}

void ServerProtocol::send_game_image(GameImage& game_image) { this->send_player_image(game_image); }
