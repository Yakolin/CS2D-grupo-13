#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

class ClientHandler : public Thread
{
private:
    Socket socket;
    GamesMonitor &games_monitor;

public:
    void run() override;
};

#endif // !CLIENT_HANDLER_H
