#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <memory>
#include <vector>

#include "../../common/queue.h"
#include "../../common/thread.h"
#include "../game.h"
#include "../protocol/client_action.h"

#include "client_handler.h"

class GameLoop: public Thread {
private:
    std::vector<std::unique_ptr<ClientHandler>> players;
    std::shared_ptr<Queue<std::unique_ptr<InterfacePlayerAction>>> recv_queue;
    bool game_started;

public:
    GameLoop(std::unique_ptr<ClientHandler>&& client_creator, const std::string& game_name);
    ~GameLoop();
    void add_player(const uint16_t& player_id, std::unique_ptr<ClientHandler>&& client_to_add);
    bool is_full();
    void run() override;
    void stop() override;
    void start() override;
};

#endif  // !GAME_LOOP_H