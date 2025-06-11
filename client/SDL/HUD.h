#include "manageTexture.h"
#include "bomb.h"
#include "text.h"
#include "../tipos.h"
#include "gameConfig.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "playerView.h"
#include "../../common/game_image.h"
class HUD {
private:
    GameConfig config ;
    ManageTexture& texture_manager;
    std::unordered_map<TextView, Text> texts;
    PlayerImage player;
    BombImage bomb;
    uint8_t time;
    GameStateImage game_state;

    PlayerImage jugador_inicial();

    BombImage bomba_inicial();

    GameStateImage estado_juego_inicial();

    void load_text(const TextView& clave, const int& x, const int& y);

    void load_info(const TextView &clave, const std::string text, Color color_id, TTF_Font *font);



public:
    HUD(GameConfig& config,ManageTexture& manager);

    void load(PlayerImage& player, BombImage& bomb, uint8_t time, GameStateImage game_state);
    void update();
    void render(SDL_Renderer& renderer);
};