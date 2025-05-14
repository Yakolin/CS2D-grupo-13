#include "protocol.h"

ServerProtocol::ServerProtocol(Socket &socket) : socket(socket) {}

ServerProtocol::~ServerProtocol() {}

void ServerProtocol::read_byte_data(uint8_t &data)
{
    uint8_t data_readed;
    this->socket.recvall(&data_readed, sizeof(uint8_t));
    if (this->socket.is_stream_recv_closed())
    {
        throw ConnectionClosedException("El cliente cerró la conexión");
    }
    data = data_readed;
}

PlayerCommandType ServerProtocol::read_player_command()
{
    player_command_t command;
    this->read_byte_data(command);
    return static_cast<PlayerCommandType>(command);
}

std::unique_ptr<PlayerAction> ServerProtocol::read_move(player_id_t player_id)
{
    move_t move_type;
    this->socket.recvall(&move_type, sizeof(move_t));
    return std::make_unique<Move>(player_id, static_cast<MoveType>(move_type));
}