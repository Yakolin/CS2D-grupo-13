#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_
//  "Copyright 2025 Yaco Santamarina"
#include "Player.h"
#include "Map.h"
#include "GameImage.h"
#include <map>
class GameManager {
private:
  std::string game_name;
  std::map<int, Player> players;
  int round = 0;
  Map map_game;
  bool game_started = false;
  void handle_player_action(int id ,float x, float y);
  GameImage generate_game_image();
public:
  explicit GameManager(const std::string&_game_name, const std::string& map_name) : game_name(_game_name) , map_game(map_name) {}
  ~GameManager();
  void add_player(std::string&&_nick_name, int id);
  GameImage frame(/*vector <PlayerAction>*/);
  void start_game();
  void stop_game();
};

#endif // GAME_MANAGER_H_
