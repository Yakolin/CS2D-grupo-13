#include "sender.h"

Sender::Sender(Socket& socket, Queue<std::unique_ptr<InterfaceClientAction>>& send_queue):
        protocol(socket), send_queue(send_queue) {}

Sender::~Sender() {}

void Sender::run() {}
