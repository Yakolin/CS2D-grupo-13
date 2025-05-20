#ifndef LOBBY_HANDLER_H
#define LOBBY_HANDLER_H

#include "../../common/connection_closed_exception.h"
#include "../../common/lobby_types.h"
#include "../../common/player_types.h"
#include "../../common/socket.h"
#include "../../common/thread.h"
#include "../protocol/protocol.h"

#include "games_monitor.h"
#include "player_handler.h"

class PlayerHandler;

class LobbyHandler: public Thread {
private:
    player_id_t client_id;
    Socket socket;
    GamesMonitor& games_monitor;
    ServerProtocol protocol;
    bool in_lobby;
    void send_handshake();

public:
    LobbyHandler(player_id_t client_id, Socket&& socket, GamesMonitor& games_monitor);
    ~LobbyHandler();

    void run() override;
    void stop() override;
    void send_list_games(std::vector<std::string>& list_games);
    std::unique_ptr<PlayerHandler> start_game(
            std::shared_ptr<Queue<std::unique_ptr<InterfacePlayerAction>>>& recv_player_queue);
};


#endif  // !LOBBY_HANDLER_H