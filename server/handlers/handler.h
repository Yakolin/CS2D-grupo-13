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
    player_id_t client_id;
    Socket socket;

public:
    Handler(player_id_t client_id, Socket&& socket):
            client_id(client_id), socket(std::move(socket)) {}

    // move-ctor: mueve id y socket
    Handler(Handler&& other) noexcept:
            client_id(other.client_id), socket(std::move(other.socket)) {}

    virtual ~Handler() = default;

    Handler(const Handler&) = delete;
    Handler& operator=(const Handler&) = delete;
};

class LobbyHandler: public Handler, public Thread {
private:
    GamesMonitor& games_monitor;
    ServerProtocol protocol;

public:
    LobbyHandler(player_id_t client_id, Socket&& socket, GamesMonitor& games_monitor);
    ~LobbyHandler();

    void run() override;
    void stop() override;
    void send(std::unique_ptr<InterfaceSenderLobby> action);
};

class PlayerHandler: public Handler {
private:
    PlayerReceiver receiver;
    PlayerSender sender;

public:
    PlayerHandler(player_id_t id, Socket&& socket,
                  std::shared_ptr<Queue<std::unique_ptr<InterfacePlayerAction>>>& recv_game_queue);
    ~PlayerHandler();
    void start();
    void stop();
    void send(GameImage& game_image);
};

#endif  // !HANDLER_H
