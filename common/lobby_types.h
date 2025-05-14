#ifndef LOBBY_TYPES_H
#define LOBBY_TYPES_H
#include <cstdint>

using lobby_command_t = std::uint8_t;

enum class LobbyCommandType
{
    CREATE_GAME,
    JOIN_GAME,
    LIST_GAMES,
};

#endif // !LOBBY_TYPES_H