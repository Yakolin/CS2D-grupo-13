#include "sender.h"

Sender::Sender(Socket &socket) : protocol(socket), send_queue() {}
Sender::~Sender() {}