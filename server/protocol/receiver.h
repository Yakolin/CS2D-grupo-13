#ifndef RECEIVER_H
#define RECEIVER_H

#include <memory>

#include "../../common/player_types.h"
#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../common/thread.h"

#include "client_action.h"
#include "functor_parse_client_action.h"
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
    virtual void run() override = 0;
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

class PlayerReceiver: public Receiver {
private:
    std::shared_ptr<Queue<std::unique_ptr<InterfacePlayerAction>>>& recv_game_queue;

public:
    PlayerReceiver(player_id_t& player_id, Socket& socket,
                   std::shared_ptr<Queue<std::unique_ptr<InterfacePlayerAction>>>& recv_game_queue);
    ~PlayerReceiver();
    void run() override;
};

#endif  // !RECEIVER_H