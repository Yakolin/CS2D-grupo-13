#include "protocol.h"

#include <iostream>
ClientProtocol::ClientProtocol(Socket& socket): socket(socket) {}

ClientProtocol::~ClientProtocol() {}

GameInfo ClientProtocol::read_game_info() {
    GameInfo game_info;
    length_game_info_t info_size;
    this->read_two_byte_data(info_size);

    for (length_game_info_t i = 0; i < info_size; ++i) {
        coordinate_t x, y;
        this->read_two_byte_data(x);
        this->read_two_byte_data(y);
        game_info.walls.emplace_back(Position(x, y));
    }
    return game_info;
}

std::vector<std::string> ClientProtocol::read_list_games() {
    length_games_list_t list_size;
    this->read_two_byte_data(list_size);

    std::vector<std::string> games_list;
    games_list.reserve(list_size);

    for (length_games_list_t i = 0; i < list_size; i++) {
        length_string_t name_length;
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

void ClientProtocol::send_string(std::string& string) {
    uint16_t length = static_cast<uint16_t>(string.size());
    this->send_two_byte_data(length);
    this->socket.sendall(string.c_str(), string.size());

    if (this->socket.is_stream_send_closed()) {
        throw ConnectionClosedException("Error al intentar enviar string al servidor");
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

void ClientProtocol::send_create_game(const CreateGame& create_game) {
    uint8_t header = static_cast<uint8_t>(LobbyCommandType::CREATE_GAME);
    this->send_byte_data(header);
    std::string game_name = create_game.game_name;
    std::string map_name = create_game.map_name;
    this->send_string(game_name);
    this->send_string(map_name);
}

void ClientProtocol::send_join_game(const JoinGame& join_game) {
    uint8_t header = static_cast<uint8_t>(LobbyCommandType::JOIN_GAME);
    this->send_byte_data(header);
    std::string game_name = join_game.game_name;
    this->send_string(game_name);
}

void ClientProtocol::send_list_games() {
    uint8_t header = static_cast<uint8_t>(LobbyCommandType::LIST_GAMES);
    this->send_byte_data(header);
}

void ClientProtocol::send_move(MoveType& move_type) {
    uint8_t move_command = static_cast<uint8_t>(PlayerCommandType::MOVE);
    uint8_t move_type_byte = static_cast<uint8_t>(move_type);
    this->send_byte_data(move_command);
    this->send_byte_data(move_type_byte);
}

void ClientProtocol::send_buy_weapon(WeaponCode& weapon_code) {
    player_command_t buy_weapon_header =
            static_cast<player_command_t>(PlayerCommandType::BUY_WEAPON);
    weapon_code_t weapon_code_command = static_cast<weapon_code_t>(weapon_code);
    this->send_byte_data(buy_weapon_header);
    this->send_byte_data(weapon_code_command);
}

void ClientProtocol::send_buy_ammo(WeaponType& weapon_type, ammo_t& ammo_count) {
    player_command_t buy_ammo_header = static_cast<player_command_t>(PlayerCommandType::BUY_AMMO);
    weapon_code_t weapon_code_command = static_cast<weapon_code_t>(weapon_type);
    ammo_t ammo_command = static_cast<ammo_t>(ammo_count);
    this->send_byte_data(buy_ammo_header);
    this->send_byte_data(weapon_code_command);
    this->send_two_byte_data(ammo_command);
}

void ClientProtocol::send_reload() {
    player_command_t reload_header = static_cast<player_command_t>(PlayerCommandType::RELOAD);
    this->send_byte_data(reload_header);
}

void ClientProtocol::send_shoot(coordinate_t& mouse_x, coordinate_t& mouse_y) {
    player_command_t shoot_header = static_cast<player_command_t>(PlayerCommandType::SHOOT);
    this->send_byte_data(shoot_header);
    this->send_two_byte_data(mouse_x);
    this->send_two_byte_data(mouse_y);
}


void ClientProtocol::send_plant_bomb() {
    player_command_t plant_bomb_header =
            static_cast<player_command_t>(PlayerCommandType::PLANT_BOMB);
    this->send_byte_data(plant_bomb_header);
}

void ClientProtocol::send_defuse_bomb() {
    player_command_t defuse_bomb_header =
            static_cast<player_command_t>(PlayerCommandType::DEFUSE_BOMB);
    this->send_byte_data(defuse_bomb_header);
}

void ClientProtocol::send_drop() {
    player_command_t drop_header = static_cast<player_command_t>(PlayerCommandType::DROP);
    this->send_byte_data(drop_header);
}

void ClientProtocol::send_equip(EquipType& equip_type) {
    player_command_t equip_header = static_cast<player_command_t>(PlayerCommandType::EQUIP);
    equip_type_t equip_type_command = static_cast<equip_type_t>(equip_type);
    this->send_byte_data(equip_header);
    this->send_byte_data(equip_type_command);
}


void ClientProtocol::send_mouse_position(coordinate_t& mouse_x, coordinate_t& mouse_y) {
    player_command_t watch_header = static_cast<player_command_t>(PlayerCommandType::WATCH);
    this->send_byte_data(watch_header);
    this->send_two_byte_data(mouse_x);
    this->send_two_byte_data(mouse_y);
}

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

void ClientProtocol::read_client_id(GameImage& game_image) {
    player_id_t client_id;
    this->read_two_byte_data(client_id);
    game_image.client_id = client_id;
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
        std::vector<WeaponImage> weapons;  // Falta implementar
        Team team = Team::CT;              // Falta implementar
        game_image.players_images.emplace_back(
                PlayerImage(player_id, Position(x, y), health, points, std::move(weapons), team));
    }
}

GameImage ClientProtocol::read_game_image() {
    GameImage game_image;

    this->read_client_id(game_image);
    this->read_player_image(game_image);

    return game_image;
}
