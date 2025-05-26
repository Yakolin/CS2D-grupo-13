#ifndef LOBBY_TYPES_H
#define LOBBY_TYPES_H
#include <cstdint>
#include <string>
using lobby_command_t = std::uint8_t;
using length_name_t = std::uint16_t;
using length_games_list_t = std::uint16_t;

enum class LobbyCommandType { CREATE_GAME, JOIN_GAME, LIST_GAMES, EXIT_GAME, HELP_GAME, NONE };


#endif  // !LOBBY_TYPES_H