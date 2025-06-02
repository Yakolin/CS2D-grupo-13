#ifndef TIPOS_H
#define TIPOS_H
#include <string>
#include <SDL2/SDL.h>

enum class GameMenu { CREATE, JOIN, HELP, EXIT, NONE };

enum class ItemTerrorism { PHOENIX, L337_KREW, ARCTIC_AVENGER, GUERRILLA };

enum class ItemCounterTerrorism { SEAL, GSG9, SAS, GIGN };

enum class Object {
    STONE,
    WALL,
    GRASS,
    BOX,
    PLAYER,
    WATER,

    PHOENIX,
    L337_KREW,
    ARCTIC_AVENGER,
    GUERRILLA,
    SEAL,
    GSG9,
    SAS,
    GIGN,
    VIDA,
    MUERTES,
    PUNTOS,
    NOMBRE,
    BANDO,

    ZONE_TERRORIST,
    ZONE_COUNTERTERROSIT,
    ZONE_BOMBA1,
    ZONE_BOMBA2

};

// campo en el desierto, un pueblito azteca o una zona de entrenamiento
enum class Map { DESIERTO, PUEBLITO_AZTECA, ZONA_ENTRENAMIENTO };


enum class Movement { UP, DOWN, LEFT, RIGHT, NONE };

struct InfoGame {
    std::string name_player;
    std::string name_game;
};

struct Player {
    std::string team;
    std::string skin;
    InfoGame info;
    std::string map;
};

struct MedidasSprites {
    int width;
    int height;
};
struct infoPlayer{
    std::string name_game;
    std::string team;
    int puntos;
    int vida ;
    int muertes;
};
struct TextureData {
    SDL_Texture* texture;
    int width;
    int height;
};

struct ItemSprite {
    int fil;
    int col;
};

struct PlayerSummary {
    int kills;
    int deaths;
    int collected_money;
};

struct Rankings {
    int ranking_terrorists;
    int ranking_counter_terrorists;
};

#endif
