#ifndef GAME_GAME_H_
#define GAME_GAME_H_
//  "Copyright 2025 Yaco Santamarina"
#include "Player.h"
#include "Map.h"
#include "GameImage.h"
#include <map>
class Game {
private:
  std::string game_name;
  std::map<int, Player> players;
  int round = 0;
  Map map_game;
  bool game_started = false;

public:
  explicit Game(const std::string&_game_name, const std::string& map_name) : game_name(_game_name) , map_game(map_name) {}
  ~Game();
  void add_player(std::string&&_nick_name, int id);
  void handle_player_action(int id ,float x, float y);
  GameImage generate_game_image();
  void start_game();
  void stop_game();
};

#endif // GAME_GAME_H_
