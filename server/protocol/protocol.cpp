#include "protocol.h"

using ServerSpace::Move;
/*
using ServerSpace::BuyAmmo;
using ServerSpace::BuyWeapon;
using ServerSpace::Equip;
using ServerSpace::Shoot;
*/
#include <iostream>

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

const std::string ServerProtocol::read_string() {
    length_string_t raw_length;
    this->socket.recvall(reinterpret_cast<char*>(&raw_length), sizeof(raw_length));
    if (this->socket.is_stream_recv_closed()) {
        throw ConnectionClosedException("Error al intentar leer longitud del cliente");
    }

    length_string_t length = ntohs(raw_length);
    std::vector<char> buffer(length);

    this->socket.recvall(buffer.data(), length);
    if (this->socket.is_stream_recv_closed()) {
        throw ConnectionClosedException("Error al intentar leer datos del client");
    }

    return std::string(buffer.begin(), buffer.end());
}


LobbyCommandType ServerProtocol::read_lobby_command() {
    lobby_command_t command;
    this->read_byte_data(command);
    return static_cast<LobbyCommandType>(command);
}

CreateGame ServerProtocol::read_create_game() {
    std::string game_name = this->read_string();

    map_name_t map_name;
    this->read_byte_data(map_name);

    skin_t ct_skin;
    this->read_byte_data(ct_skin);

    skin_t tt_skin;
    this->read_byte_data(tt_skin);

    return CreateGame(
            game_name, static_cast<MapName>(map_name),
            Skins(static_cast<CounterTerroristSkin>(ct_skin), static_cast<TerroristSkin>(tt_skin)));
}

JoinGame ServerProtocol::read_join_game() {
    std::string game_name = this->read_string();

    skin_t ct_skin;
    this->read_byte_data(ct_skin);

    skin_t tt_skin;
    this->read_byte_data(tt_skin);

    return JoinGame(game_name, Skins(static_cast<CounterTerroristSkin>(ct_skin),
                                     static_cast<TerroristSkin>(tt_skin)));
}

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

void ServerProtocol::send_position(const Position& position) {
    coordinate_t x = position.x;
    this->send_two_byte_data(x);

    coordinate_t y = position.y;
    this->send_two_byte_data(y);
}

void ServerProtocol::send_list_games(ListGame& games) {
    std::vector<std::string> list_games = games.list_games;
    length_games_list_t list_size = list_games.size();
    this->send_two_byte_data(list_size);

    for (const std::string& game_name: list_games) {
        length_string_t name_length = game_name.size();
        this->send_two_byte_data(name_length);

        this->socket.sendall(game_name.data(), name_length);
        if (this->socket.is_stream_send_closed()) {
            throw ConnectionClosedException("Error al intentar enviar datos al cliente");
        }
    }
}

void ServerProtocol::send_game_info(GameInfo& game_info) {
    std::vector<Position> walls = game_info.walls;
    length_game_info_t info_size = walls.size();
    this->send_two_byte_data(info_size);

    for (const Position& wall_position: walls) {
        this->send_position(wall_position);
    }
}

void ServerProtocol::send_client_id(GameImage& game_image) {
    player_id_t client_id = game_image.client_id;
    this->send_two_byte_data(client_id);
}

void ServerProtocol::send_player_image(GameImage& game_image) {

    std::vector<PlayerImage> players_images = game_image.players_images;
    length_players_images_t length_players = players_images.size();
    this->send_two_byte_data(length_players);

    for (const PlayerImage& player_image: players_images) {
        player_id_t player_id = player_image.player_id;
        this->send_two_byte_data(player_id);

        this->send_position(player_image.position);

        health_t health = player_image.health;
        this->send_byte_data(health);

        points_t points = player_image.points;
        this->send_byte_data(points);
    }
}

void ServerProtocol::send_game_image(GameImage& game_image) {
    this->send_client_id(game_image);
    this->send_player_image(game_image);
}