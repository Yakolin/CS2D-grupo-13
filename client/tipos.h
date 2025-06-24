#ifndef TIPOS_H
#define TIPOS_H
#include <string>

#include <SDL2/SDL.h>

#include "../common/game_info.h"
#include "../common/player_command_types.h"

enum class GameMenu { CREATE, JOIN, HELP, EXIT, NONE };

enum class TextView {
    HEALTH,
    AMMO,
    TIME,
    POINTS,
    TEAM,
    BOMB,
    MONEY,
    WEAPON,
    BULLETS,
    NONE,
    BUY,
    WIN_GAME_TT,
    WIN_GAME_CT,
    WIN_ROUND_TT,
    WIN_ROUND_CT,
    ROUND
};

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


enum class Music { SALA_ESPERA, JUEGO };


enum class ColorTranslucent {
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

enum class CursorContext { NORMAL, ENEMY, ALLY,CARGANDO };


enum class EffectType { EXPLOSION, PIP, WIN_CT, WIN_TT, ACTIVATION, DESACTIVATED,MOUSE };

enum class Object {

    TT,
    CT,

    MOUSE,
    STONE,
    WALL_AZTEC,
    WALL_ENTRENAMIENTO,
    WALL_DESIERTO,

    FONDO_ESPERA,
    ROUND,

    GRASS,
    BOX1,
    BOX3,
    BOX2,
    BOX4,
    BOX5,
    BOX6,
    PARASOL1,
    PARASOL2,

    WATER,
    VIDA,
    MUERTES,
    PUNTOS,
    NOMBRE,
    BANDO,
    EXPLOSION,
    BULLET,

    MUERTE,
    TIMER,
    TIMER_BOMB,
    TIENDA,
    MONEY,
    BALA,

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

    TREE_AZTEC,
    TREE_ENTRENAMIENTO,
    TREE_DESIERTO,

    FLOOR_AZTEC,
    FLOOR_ENTRENAMIENTO,
    FLOOR_DESIERTO,

    ZONE_TERRORIST,
    ZONE_COUNTERTERROSIT,
    ZONE_BOMBA,
    ZONE_BOMBB
};


// campo en el desierto, un pueblito azteca o una zona de entrenamiento
enum class Map { DESIERTO, PUEBLITO_AZTECA, ZONA_ENTRENAMIENTO };


enum class Movement { UP, DOWN, LEFT, RIGHT, NONE };

struct InfoGame {
    std::string name_player;
    std::string name_game;
};

struct Claves_skins {
    CounterTerroristSkin ct_skin;
    TerroristSkin tt_skin;
};

struct Player {
    std::string team;
    std::string skin_ct;
    std::string skin_tt;
    InfoGame info;
    std::string map;
};

struct MedidasSprites {
    int width;
    int height;
};
struct InfoPlayer {
    std::string name_player;
    std::string team;
    int puntos;
    int deaths;
    int kills;
    int collected_money;
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
struct TextureInfo {
    SDL_Texture* textura;
    SDL_Rect medidas;
};
#endif  // TIPOS_H
