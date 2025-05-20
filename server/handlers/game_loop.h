#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <memory>
#include <vector>

#include "../../common/queue.h"
#include "../../common/thread.h"
#include "../game.h"
#include "../protocol/client_action.h"

#include "lobby_handler.h"
#include "player_handler.h"

class PlayerHandler;
class LobbyHandler;
class InterfacePlayerAction;

#define QUEUE_MAX_SIZE 10000

class GameLoop: public Thread {
private:
    const std::string& game_name;
    std::vector<std::unique_ptr<PlayerHandler>> players;
    std::shared_ptr<Queue<std::unique_ptr<InterfacePlayerAction>>> recv_queue;
    bool game_started;
    void step();

public:
    GameLoop(LobbyHandler& client_creator, const std::string& game_name);
    ~GameLoop();
    void add_player(LobbyHandler& client_to_add);
    bool is_full();
    void run() override;
    void stop() override;
    void start() override;
};

#endif  // !GAME_LOOP_H