#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <memory>
#include <vector>

#include "../../common/constant_rate_loop.h"
#include "../../common/game_image.h"
#include "../../common/queue.h"
#include "../../common/thread.h"
#include "../interfaces/interface_game.h"
#include "../game/GameManager.h"
#include "client_action.h"


#define QUEUE_MAX_SIZE 10000
#define MAX_PLAYERS 2

class GameLoop: public Thread {
private:
    const std::string& game_name;
    GameManager game;
    std::vector<std::shared_ptr<Queue<GameImage>>> send_queues;
    std::shared_ptr<Queue<std::unique_ptr<ClientAction>>> recv_queue;
    ConstantRateLoop constant_rate_loop;
    bool game_started;

    void step();
    void broadcast(GameImage& game_image);

public:
    GameLoop(const std::string& game_name);
    ~GameLoop();
    void add_player(player_id_t& player_id,
                    std::shared_ptr<Queue<std::unique_ptr<ClientAction>>>& recv_queue,
                    std::shared_ptr<Queue<GameImage>>& send_queue);
    bool is_full();
    void run() override;
    void stop() override;
};

#endif  // !GAME_LOOP_H