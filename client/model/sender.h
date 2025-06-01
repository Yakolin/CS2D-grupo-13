#ifndef SENDER_H
#define SENDER_H

#include <memory>

#include "../../common/connection_closed_exception.h"
#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../common/thread.h"

#include "client_action.h"
#include "protocol.h"


class Sender: public Thread {
private:
    bool closed;
    ClientProtocol protocol;
    std::shared_ptr<Queue<std::unique_ptr<InterfaceClientAction>>>& send_queue;

public:
    explicit Sender(Socket& socket,
                    std::shared_ptr<Queue<std::unique_ptr<InterfaceClientAction>>>& send_queue);
    explicit Sender(Socket& socket,
                    std::shared_ptr<Queue<std::unique_ptr<InterfaceClientAction>>>& send_queue);
    ~Sender() override;

    void run() override;

    void stop() override;
};

#endif  // !SENDER_H
