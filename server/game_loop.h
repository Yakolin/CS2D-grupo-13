#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "common/thread.h"
#include <map>

#include "player.h"

class GameLoop : public Thread
{
private:
    std::map<std::string, std::unique_ptr<Player>> players;

public:
    GameLoop() = default;
    ~GameLoop() = default;
    void add_player(const std::string &player_name);
    void run() override;
    void stop() override;
};

#endif // !GAME_LOOP_H