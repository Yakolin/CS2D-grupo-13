#ifndef RECEIVER_H
#define RECEIVER_H

#include <memory>

#include "common/player_types.h"
#include "common/queue.h"
#include "common/socket.h"
#include "common/thread.h"

#include "client_action.h"
#include "protocol.h"


class Receiver: public Thread {
protected:
    player_id_t& player_id;
    ServerProtocol protocol;
    bool closed;

public:
    Receiver(player_id_t& player_id, Socket& socket):
            player_id(player_id), protocol(socket), closed(false) {}
    virtual ~Receiver() = default;
};

class LobbyReceiver: public Receiver {
private:
    std::shared_ptr<Queue<std::unique_ptr<InterfaceLobbyAction>>>& recv_lobby_queue;

public:
    LobbyReceiver(player_id_t& player_id, Socket& socket,
                  std::shared_ptr<Queue<std::unique_ptr<InterfaceLobbyAction>>>& recv_lobby_queue);
    ~LobbyReceiver();
    void run() override;
};

class GameReceiver: public Receiver {
private:
    std::shared_ptr<Queue<std::unique_ptr<InterfacePlayerAction>>>& recv_game_queue;

public:
    GameReceiver(player_id_t& player_id, Socket& socket,
                 std::shared_ptr<Queue<std::unique_ptr<InterfacePlayerAction>>>& recv_game_queue);
    ~GameReceiver();
    void run() override;
};

#endif  // !RECEIVER_H