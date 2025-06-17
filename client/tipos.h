#ifndef TIPOS_H
#define TIPOS_H
#include <string>
#include "../common/player_command_types.h"
#include "../common/game_info.h"
#include <SDL2/SDL.h>

enum class GameMenu { CREATE, JOIN, HELP, EXIT, NONE };

enum class TextView { HEALTH, AMMO, TIME, POINTS, TEAM, BOMB, MONEY, WEAPON, BULLETS, NONE };

enum class Color {
    ROJO,
    VERDE,
    AZUL,
    BLANCO,
    NEGRO,
    AMARILLO,
    CIAN,
    MAGENTA,
    GRIS,
    NARANJA,
    VIOLETA,
    ROSADO
};

enum class Weapon {
    AK47,
    M4A1,
    AUG,
    FAMAS,
    GALIL,
    SCAR20,
    AWP,
    SSG08,
    P90,
    MP5,
    UMP45,
    MAC10,
    P250,
    DEAGLE,
    GLOCK,
    SNIKE,
    BOMB,
    M3,
    NONE
};
enum class Object {
    STONE,
    WALL_AZTEC,
    WALL_ENTRENAMIENTO,
    WALL_DESIERTO,

    GRASS,
    BOX,
    PLAYER,
    WATER,
    VIDA,
    MUERTES,
    PUNTOS,
    NOMBRE,
    BANDO,
    EXPLOSION,
    BULLET,

    TREE_AZTEC,
    TREE_ENTRENAMIENTO,
    TREE_DESIERTO,

    FLOOR_AZTEC,
    FLOOR_ENTRENAMIENTO,
    FLOOR_DESIERTO,

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

struct Claves_skins{
    CounterTerroristSkin ct_skin;
    TerroristSkin tt_skin;
};

struct Player {
    std::string team;
    std::string skin;
    std::string skin2;
    InfoGame info;
    std::string map;
};

struct MedidasSprites {
    int width;
    int height;
};
struct infoPlayer {
    std::string name_game;
    std::string team;
    int puntos;
    int vida;
    int muertes;
};
struct TextureData {
    SDL_Texture* texture;
    int width;
    int height;
};
struct Coordenada {
    float x;
    float y;
};
struct CoordenadaInt {
    int x;
    int y;
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
struct ShopItem {
    SDL_Texture* texture;
    int price;
    std::string name;
    SDL_Rect destRect;
    std::string descripcion;
};
struct WeaponData {
    WeaponCode clave;
    std::string name;
    int price;
    std::string descripcion;
};
struct Rankings {
    int ranking_terrorists;
    int ranking_counter_terrorists;
};

#endif  // TIPOS_H
