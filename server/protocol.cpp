#include "protocol.h"

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

PlayerCommandType ServerProtocol::read_player_command() {
    player_command_t command;
    this->read_byte_data(command);
    return static_cast<PlayerCommandType>(command);
}

std::unique_ptr<Move> ServerProtocol::read_move(player_id_t player_id) {
    move_t move_type;
    this->socket.recvall(&move_type, sizeof(move_t));
    return std::make_unique<Move>(player_id, static_cast<MoveType>(move_type));
}

std::unique_ptr<BuyWeapon> ServerProtocol::read_buy_weapon(player_id_t player_id) {
    weapon_code_t weapon_code;
    this->socket.recvall(&weapon_code, sizeof(weapon_code_t));
    return std::make_unique<BuyWeapon>(player_id, static_cast<WeaponCode>(weapon_code));
}

std::unique_ptr<BuyAmmo> ServerProtocol::read_buy_ammo(player_id_t player_id) {
    weapon_type_t weapon_type;
    ammo_t ammo_count;
    this->socket.recvall(&weapon_type, sizeof(weapon_type_t));
    this->socket.recvall(&ammo_count, sizeof(ammo_t));
    return std::make_unique<BuyAmmo>(player_id, static_cast<WeaponType>(weapon_type), ammo_count);
}

std::unique_ptr<Reload> ServerProtocol::read_reload(player_id_t player_id) {
    weapon_type_t weapon_type;
    this->socket.recvall(&weapon_type, sizeof(weapon_type_t));
    return std::make_unique<Reload>(player_id, static_cast<WeaponType>(weapon_type));
}

std::unique_ptr<Shoot> ServerProtocol::read_shoot(player_id_t player_id) {
    weapon_type_t weapon_type;
    ammo_t ammo_count;
    this->socket.recvall(&weapon_type, sizeof(weapon_type_t));
    this->socket.recvall(&ammo_count, sizeof(ammo_t));
    return std::make_unique<Shoot>(player_id, static_cast<WeaponType>(weapon_type), ammo_count);
}

std::unique_ptr<DropWeapon> ServerProtocol::read_drop_weapon(player_id_t player_id) {
    weapon_type_t weapon_type;
    this->socket.recvall(&weapon_type, sizeof(weapon_type_t));
    return std::make_unique<DropWeapon>(player_id, static_cast<WeaponType>(weapon_type));
}

std::unique_ptr<PlantBomb> ServerProtocol::read_plant_bomb(player_id_t player_id) {
    return std::make_unique<PlantBomb>(player_id);
}

std::unique_ptr<DefuseBomb> ServerProtocol::read_defuse_bomb(player_id_t player_id) {
    return std::make_unique<DefuseBomb>(player_id);
}

std::unique_ptr<DropBomb> ServerProtocol::read_drop_bomb(player_id_t player_id) {
    return std::make_unique<DropBomb>(player_id);
}
