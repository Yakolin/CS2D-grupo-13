#ifndef SENDER_H
#define SENDER_H

#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../common/thread.h"

#include "client_action.h"
#include "protocol.h"


class Sender: public Thread {
private:
    ClientProtocol protocol;
    Queue<std::unique_ptr<InterfaceClientAction>>& send_queue;

public:
    explicit Sender(Socket& socket, Queue<std::unique_ptr<InterfaceClientAction>>& send_queue);
    ~Sender() override;

    void run() override;
    void stop() override;
};

#endif  // !SENDER_H