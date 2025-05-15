#ifndef SENDER_H
#define SENDER_H

#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../common/thread.h"

#include "protocol.h"


class

        class Sender: public Thread {
private:
    Queue<>& send_queue;
    ClientProtocol protocol;

public:
    explicit Sender(Socket& socket, Queue<GameImage>& send_queue);
    ~Sender() override;

    void send_lobby_action();
    void send_player_action();

    void run() override;
    void stop() override;
};

#endif  // !SENDER_H