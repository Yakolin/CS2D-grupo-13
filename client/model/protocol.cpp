#include "protocol.h"

#include <iostream>
ClientProtocol::ClientProtocol(Socket& socket): socket(socket) {}

ClientProtocol::~ClientProtocol() {}


std::vector<std::string> ClientProtocol::read_list_games() {
    length_games_list_t list_size;
    this->read_two_byte_data(list_size);

    std::vector<std::string> games_list;
    games_list.reserve(list_size);

    for (length_games_list_t i = 0; i < list_size; i++) {
        length_name_t name_length;
        this->read_two_byte_data(name_length);

        std::vector<char> buffer(name_length);
        this->socket.recvall(buffer.data(), name_length);

        if (this->socket.is_stream_recv_closed()) {
            throw ConnectionClosedException("Error al intentar recibir datos del servidor");
        }
        std::string game_name(buffer.data(), name_length);
        games_list.push_back(std::move(game_name));
    }
    return games_list;
}

void ClientProtocol::send_byte_data(uint8_t& data) {
    this->socket.sendall(&data, sizeof(uint8_t));
    if (this->socket.is_stream_send_closed()) {
        throw ConnectionClosedException("Error al intentar enviar datos al servidor");
    }
}

void ClientProtocol::send_two_byte_data(uint16_t& data) {
    uint16_t data_to_send = htons(data);
    this->socket.sendall(&data_to_send, sizeof(uint16_t));
    if (this->socket.is_stream_send_closed()) {
        throw ConnectionClosedException("Error al intentar enviar datos al servidor");
    }
}

void ClientProtocol::send_lobby_command(LobbyCommandType command) {
    uint8_t command_byte = static_cast<uint8_t>(command);
    this->send_byte_data(command_byte);
}

void ClientProtocol::send_player_command(PlayerCommandType command) {
    uint8_t command_byte = static_cast<uint8_t>(command);
    this->send_byte_data(command_byte);
}

void ClientProtocol::send_create_game(const std::string& game_name) {
    uint8_t header = static_cast<uint8_t>(LobbyCommandType::CREATE_GAME);
    this->send_byte_data(header);

    uint16_t length = static_cast<uint16_t>(game_name.size());
    this->send_two_byte_data(length);
    this->socket.sendall(game_name.c_str(), game_name.size());
    if (this->socket.is_stream_send_closed()) {
        throw ConnectionClosedException("Error al intentar enviar datos al servidor");
    }
}

void ClientProtocol::send_join_game(const std::string& game_name) {
    uint8_t header = static_cast<uint8_t>(LobbyCommandType::JOIN_GAME);
    this->send_byte_data(header);

    uint16_t length = static_cast<uint16_t>(game_name.size());
    this->send_two_byte_data(length);
    this->socket.sendall(game_name.c_str(), game_name.size());
    if (this->socket.is_stream_send_closed()) {
        throw ConnectionClosedException("Error al intentar enviar datos al servidor");
    }
}

void ClientProtocol::send_list_games() {
    uint8_t header = static_cast<uint8_t>(LobbyCommandType::LIST_GAMES);
    this->send_byte_data(header);
}

void ClientProtocol::send_move(MoveType move_type) {
    uint8_t move_command = static_cast<uint8_t>(PlayerCommandType::MOVE);
    uint8_t move_type_byte = static_cast<uint8_t>(move_type);
    this->send_byte_data(move_command);
    this->send_byte_data(move_type_byte);
}

void ClientProtocol::send_buy_weapon(WeaponCode weapon_code) {
    socket.sendall(reinterpret_cast<const char*>(&weapon_code), sizeof(weapon_code));
}

void ClientProtocol::send_buy_ammo(WeaponType weapon_type, ammo_t ammo_count) {
    socket.sendall(reinterpret_cast<const char*>(&weapon_type), sizeof(weapon_type));
    socket.sendall(reinterpret_cast<const char*>(&ammo_count), sizeof(ammo_count));
}

void ClientProtocol::send_reload(WeaponType weapon_type) {
    socket.sendall(reinterpret_cast<const char*>(&weapon_type), sizeof(weapon_type));
}

void ClientProtocol::send_shoot(WeaponType weapon_type, ammo_t ammo_count) {
    socket.sendall(reinterpret_cast<const char*>(&weapon_type), sizeof(weapon_type));
    socket.sendall(reinterpret_cast<const char*>(&ammo_count), sizeof(ammo_count));
}

void ClientProtocol::send_drop() {}

void ClientProtocol::send_plant_bomb() {}

void ClientProtocol::send_defuse_bomb() {}

void ClientProtocol::read_byte_data(uint8_t& data) {
    uint8_t data_readed;
    this->socket.recvall(&data_readed, sizeof(uint8_t));
    if (this->socket.is_stream_recv_closed()) {
        throw ConnectionClosedException("El cliente cerró la conexión");
    }
    data = data_readed;
}

void ClientProtocol::read_two_byte_data(uint16_t& data) {
    uint16_t data_readed;
    this->socket.recvall(&data_readed, sizeof(uint16_t));
    if (this->socket.is_stream_recv_closed()) {
        throw ConnectionClosedException("El cliente cerró la conexión");
    }
    data = ntohs(data_readed);
}


void ClientProtocol::read_player_image(GameImage& game_image) {

    length_players_images_t length_players_images;
    this->read_two_byte_data(length_players_images);
    for (auto i = 0; i < length_players_images; ++i) {
        player_id_t player_id;
        this->read_two_byte_data(player_id);

        coordinate_t x;
        this->read_two_byte_data(x);
        coordinate_t y;
        this->read_two_byte_data(y);

        health_t health;
        this->read_byte_data(health);

        points_t points;
        this->read_byte_data(points);

        game_image.players_images.emplace_back(
                PlayerImage(player_id, Position(x, y), health, points));
    }
}


GameImage ClientProtocol::read_game_image() {
    GameImage game_image;

    this->read_player_image(game_image);

    return game_image;
}
