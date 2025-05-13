#include "protocol.h"

ServerProtocol::ServerProtocol(Socket &socket) : socket(socket) {}

ServerProtocol::~ServerProtocol() {}
