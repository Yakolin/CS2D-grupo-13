#include "protocol.h"

using Server::BuyAmmo;
using Server::BuyWeapon;
using Server::CreateGame;
using Server::DefuseBomb;
using Server::Drop;
using Server::Equip;
using Server::JoinGame;
using Server::ListGames;
using Server::Move;
using Server::PlantBomb;
using Server::Reload;
using Server::Shoot;

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
    uint16_t dataReaded;
    this->socket.recvall(&dataReaded, sizeof(uint16_t));
    if (this->socket.is_stream_recv_closed()) {
        throw ConnectionClosedException("El cliente cerró la conexión");
    }
    data = ntohs(dataReaded);
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

std::unique_ptr<CreateGame> ServerProtocol::read_create_game(player_id_t player_id) {
    std::string game_name = this->read_game_name();
    return std::make_unique<CreateGame>(player_id, std::string(game_name));
}

std::unique_ptr<JoinGame> ServerProtocol::read_join_game(player_id_t player_id) {
    std::string game_name = this->read_game_name();
    return std::make_unique<JoinGame>(player_id, std::string(game_name));
}

std::unique_ptr<ListGames> ServerProtocol::read_list_games(player_id_t player_id) {
    return std::make_unique<ListGames>(player_id);
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

std::unique_ptr<Reload> ServerProtocol::read_reload(player_id_t player_id) {
    return std::make_unique<Reload>(player_id);
}

std::unique_ptr<Shoot> ServerProtocol::read_shoot(player_id_t player_id) {
    coordinate_t x;
    coordinate_t y;
    ammo_t ammo_count;
    this->read_two_byte_data(x);
    this->read_two_byte_data(y);
    this->read_two_byte_data(ammo_count);
    return std::make_unique<Shoot>(player_id, Position(x, y), ammo_count);
}

std::unique_ptr<PlantBomb> ServerProtocol::read_plant_bomb(player_id_t player_id) {
    return std::make_unique<PlantBomb>(player_id);
}

std::unique_ptr<DefuseBomb> ServerProtocol::read_defuse_bomb(player_id_t player_id) {
    return std::make_unique<DefuseBomb>(player_id);
}

std::unique_ptr<Drop> ServerProtocol::read_drop(player_id_t player_id) {
    return std::make_unique<Drop>(player_id);
}

std::unique_ptr<Equip> ServerProtocol::read_equip(player_id_t player_id) {
    equip_type_t equip_type;
    this->read_byte_data(equip_type);
    return std::make_unique<Equip>(player_id, static_cast<EquipType>(equip_type));
}
