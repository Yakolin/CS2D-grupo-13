#include "protocol.h"

ClientProtocol::ClientProtocol(Socket& socket): socket(socket) {}

ClientProtocol::~ClientProtocol() {}

void ClientProtocol::send_lobby_command(LobbyCommandType command) {
    socket.sendall(reinterpret_cast<char*>(&command), sizeof(command));
}

void ClientProtocol::send_player_command(PlayerCommandType command) {
    socket.sendall(reinterpret_cast<char*>(&command), sizeof(command));
}

void ClientProtocol::send_create_game(const std::string& game_name) {
    socket.sendall(reinterpret_cast<const char*>(&game_name), sizeof(game_name));
}

void ClientProtocol::send_join_game(const std::string& game_name) {
    socket.sendall(reinterpret_cast<const char*>(&game_name), sizeof(game_name));
}

void ClientProtocol::send_list_games() {}

void ClientProtocol::send_move(MoveType move_type) {
    socket.sendall(reinterpret_cast<const char*>(&move_type), sizeof(move_type));
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

void ClientProtocol::send_drop_weapon() {}

void ClientProtocol::send_plant_bomb() {}

void ClientProtocol::send_defuse_bomb() {}

void ClientProtocol::send_drop_bomb() {}

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
    data = data_readed;
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

        game_image.players_images.emplace_back(PlayerImage(player_id, Position(x, y)));
    }
}


GameImage ClientProtocol::read_game_image() {
    GameImage game_image;

    this->read_player_image(game_image);

    return game_image;
}
