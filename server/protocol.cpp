#include "protocol.h"

ServerProtocol::ServerProtocol(Socket &socket) : socket(socket) {}

ServerProtocol::~ServerProtocol() {}

void ServerProtocol::read_byte_data(uint8_t &data)
{
    uint8_t dataReaded;
    this->socket.recvall(&dataReaded, sizeof(uint8_t));
    if (this->socket.is_stream_recv_closed())
    {
        throw ConnectionClosedException("El cliente cerró la conexión");
    }
    data = dataReaded;
}

PlayerCommandType ServerProtocol::read_player_command()
{
    player_command_t command;
    this->read_byte_data(command);
    return static_cast<PlayerCommandType>(command);
}

MoveRight ServerProtocol::read_move_right()
{
    player_id_t player_id;
    this->socket.recvall(&player_id, sizeof(player_id_t));
    return MoveRight(player_id);
}