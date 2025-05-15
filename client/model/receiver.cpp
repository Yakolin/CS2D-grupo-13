#include "receiver.h"

Receiver::Receiver(Socket& socket, Queue<GameImage>& recv_queue):
        protocol(socket), recv_queue(recv_queue) {}

Receiver::~Receiver() {}
