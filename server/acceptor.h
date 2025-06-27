#ifndef ACCEPTOR_H
#define ACCEPTOR_H
#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <utility>

#include "../common/liberror.h"
#include "../common/player_command_types.h"
#include "../common/socket.h"
#include "../common/thread.h"
#include "protocol/client_handler.h"
#include "protocol/games_monitor.h"


class Acceptor: public Thread {
private:
    Socket socket_acceptor;
    std::map<player_id_t, std::unique_ptr<ClientHandler>> clients;
    GamesMonitor games_monitor;
    uint16_t client_id_counter;

    void reap();
    void clear();

public:
    explicit Acceptor(const char* port);

    ~Acceptor();

    bool has_clients();
    void run() override;
    void stop() override;
};


#endif  // !
