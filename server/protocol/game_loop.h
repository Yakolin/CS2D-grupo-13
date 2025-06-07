#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <map>
#include <memory>

#include "../../common/constant_rate_loop.h"
#include "../../common/game_image.h"
#include "../../common/game_info.h"
#include "../../common/lobby_action.h"
#include "../../common/queue.h"
#include "../../common/thread.h"
#include "../game/GameManager.h"
#include "../interfaces/interface_game.h"

#include "client_action.h"


#define QUEUE_MAX_SIZE 10000
#define MAX_PLAYERS 2

class GameLoop: public Thread {
private:
    const std::string& game_name;
    GameManager game;
    std::map<player_id_t, std::shared_ptr<Queue<GameImage>>> send_queues;
    std::shared_ptr<Queue<std::unique_ptr<ClientAction>>> recv_queue;
    ConstantRateLoop constant_rate_loop;
    bool game_started;

    void step();
    void broadcast(GameImage& game_image);

public:
    GameLoop(const CreateGame& create_game);
    ~GameLoop();
    void add_player(player_id_t& player_id,
                    std::shared_ptr<Queue<std::unique_ptr<ClientAction>>>& recv_queue,
                    std::shared_ptr<Queue<GameImage>>& send_queue, GameInfo& game_info);
    bool is_full();
    bool waiting_for_players();
    void run() override;
    void stop() override;
};

#endif  // !GAME_LOOP_H
