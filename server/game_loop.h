#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "common/thread.h"
#include <vector>

#include "player.h"
#include "common/queue.h"
#include "player_action.h"
#include "game.h"

class GameLoop : public Thread
{
private:
    std::vector<std::unique_ptr<Player>> players;
    Queue<std::shared_ptr<PlayerAction>> recv_queue;
    Game game;
    bool game_started;

public:
    GameLoop(const std::string &game_name, const uint16_t &number_of_players);
    ~GameLoop();
    void add_player(std::unique_ptr<Player> player);
    bool is_full();
    void run() override;
    void stop() override;
    void start() override;
};

#endif // !GAME_LOOP_H