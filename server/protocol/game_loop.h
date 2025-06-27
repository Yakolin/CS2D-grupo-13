#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include <yaml-cpp/yaml.h>

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

using max_players_t = uint8_t;

class GameLoop: public Thread {
private:
    const std::string& game_name;
    GameManager game;
    std::map<player_id_t, std::shared_ptr<Queue<GameImage>>> send_queues;
    std::shared_ptr<Queue<std::unique_ptr<ClientAction>>> recv_queue;
    std::map<player_id_t, bool> players_ready;
    ConstantRateLoop constant_rate_loop;
    max_players_t max_players;
    bool game_started;

    max_players_t read_max_players_from_config(
            const std::string& path = "server/protocol/server_config.yaml");
    void end_game();
    void step();
    void broadcast(GameImage& game_image);

public:
    GameLoop(const std::string& game_name, const MapName& map_name);
    ~GameLoop();
    void add_player(player_id_t& player_id, Skins& skins,
                    std::shared_ptr<Queue<std::unique_ptr<ClientAction>>>& recv_queue,
                    std::shared_ptr<Queue<GameImage>>& send_queue, GameInfo& game_info);
    bool all_players_ready();
    void player_ready(const player_id_t& player_id);
    bool waiting_for_players();
    bool is_full();
    void run() override;
    void stop() override;
};

#endif  // !GAME_LOOP_H
