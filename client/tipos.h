#ifndef TIPOS_H
#define TIPOS_H
#include <string>

enum class GameMenu { CREATE, JOIN, HELP, EXIT ,NONE};
enum class Team { TERRORISTS, COUNTER_TERRORISTS };

// Pheonix, L337 Krew, Artic avenger o Guerrilla
enum class ItemTerrorism { PHOENIX, L337_KREW, ARCTIC_AVENGER, GUERRILLA };
// (Seal force, German GSG-9, UK SAS o French GIGN
enum class ItemCounterTerrorism { SEAL, GSG9, SAS, GIGN };

enum class Skin {  PHOENIX, L337_KREW, ARCTIC_AVENGER, GUERRILLA, SEAL, GSG9, SAS, GIGN };
// campo en el desierto, un pueblito azteca o una zona de entrenamiento
enum class Map { DESIERTO, PUEBLITO_AZTECA, ZONA_ENTRENAMIENTO };
struct Personaje{
    Team team;
    Skin skin;
    int fila;
    int columna;
};
struct InfoGame{
    GameMenu menu;
    struct Personaje personaje;
    Map map; 
};

struct PlayerSummary {
    //std::string name;
    int kills;
    int deaths;
    int collected_money;
};

struct Rankings {
    int ranking_terrorists;
    int ranking_counter_terrorists;
};

#endif
