#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

class ClientHandler : public Thread
{
private:
    Socket socket;
    GamesMonitor &games_monitor;
    void run() override;
    void stop() override;
};

#endif // !CLIENT_HANDLER_H
