#ifndef HANDLER_H
#define HANDLER_H

#include <memory>
#include <utility>

#include "../../common/lobby_types.h"
#include "../../common/player_types.h"
#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../common/thread.h"
#include "../protocol/protocol.h"
#include "../protocol/receiver.h"
#include "../protocol/sender.h"

#include "games_monitor.h"

#define QUEUE_MAX_SIZE 10000

class Handler {
protected:
    player_id_t id;
    Socket socket;

public:
    Handler(plyer_id_t id, Socket&& socket): id(id), socket(std::move(socket)) {}
    virtual ~Handler() = default
};

class LobbyHandler: public Handler, Thread {
private:
    GamesMonitor& games_monitor;
    ServerProtocol protocol;
    bool in_lobby;

public:
    LobbyHandler(player_id_t client_id, Socket&& socket, GamesMonitor& games_monitor);
    ~LobbyHandler();

    void run() override;
    void stop() override;
};

class PlayerHandler: public Handler {
private:
    PlayerReceiver receiver;
    PlayerSender sender;

public:
    PlayerHandler(player_id_t id, Socket&& socket);
    ~PlayerHandler();
};

#endif  // !HANDLER_H
