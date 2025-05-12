#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "common/thread.h"
#include <vector>

#include "player.h"
#include "common/queue.h"
#include "player_action.h"

class GameLoop : public Thread
{
private:
    std::vector<std::unique_ptr<Player>> players;
    Queue<std::shared_ptr<PlayerAction>> recv_queue;

public:
    GameLoop();
    ~GameLoop() = default;
    void add_player(std::unique_ptr<Player> player);
    void run() override;
    void stop() override;
};

#endif // !GAME_LOOP_H