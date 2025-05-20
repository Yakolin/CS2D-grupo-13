#ifndef SENDER_H
#define SENDER_H

#include <memory>

#include "../../common/game_image.h"
#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../common/thread.h"

#include "protocol.h"

#define QUEUE_MAX_SIZE 10000

class Sender: public Thread {
protected:
    ServerProtocol protocol;
    bool closed;

public:
    explicit Sender(Socket& socket): protocol(socket), closed(false) {}
    virtual ~Sender() = default;
    virtual void run() override = 0;
    virtual void stop() override = 0;
};
/*
class LobbySender: public Sender {
    private:
    Queue<std::unique_ptr<InterfaceSenderLobby>> send_lobby_queue;

    public:
    explicit LobbySender(Socket& socket);
    ~LobbySender();
    void send(std::unique_ptr<InterfaceSenderLobby>& action) override;
    void send(GameImage& game_image) override;
    void run() override;
    void stop() override;
};

*/
class PlayerSender: public Sender {
private:
    Queue<GameImage> send_game_queue;

public:
    explicit PlayerSender(Socket& socket);
    ~PlayerSender();
    void send(GameImage& game_image);
    void run() override;
    void stop() override;
};

#endif  // H
