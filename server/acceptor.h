#ifndef ACCEPTOR_H
#define ACCEPTOR_H
#include <algorithm>
#include <iostream>
#include <map>
#include <utility>

#include "../../common/liberror.h"
#include "../../common/socket.h"
#include "../../common/thread.h"

#include "client_handler.h"
#include "games_monitor.h"

class Acceptor: public Thread {
private:
    Socket socket_acceptor;
    std::map<uint16_t, std::unique_ptr<ClientHandler>> clients;
    GamesMonitor games_monitor;
    uint16_t client_id_counter;

    void reap();
    void clear();

public:
    explicit Acceptor(const char* port);

    ~Acceptor();

    void run() override;
    void stop() override;
};

#endif  // !