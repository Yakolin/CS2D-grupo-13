#include "receiver.h"

Receiver::Receiver(uint16_t &player_id, Socket &socket, Queue<std::shared_ptr<PlayerAction>> &recv_queue) : player_id(player_id), protocol(socket), recv_queue(recv_queue), closed(false) {}
Receiver::~Receiver() {}

void Receiver::run()
{
    try
    {
        while (!this->closed && this->should_keep_running()) // aca se supone que pushea de forma bloqueante a la cola las acciones del jugador, antes leo del protocolo
        {
        }
    }
    catch (ClosedQueue &e)
    {
        this->closed = true;
    }
    catch (...)
    {
        std::cerr << "Something went wrong and an unknown exception was caught." << std::endl;
        closed = true;
    }
}