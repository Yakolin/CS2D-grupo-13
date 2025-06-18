#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../../common/game_image.h"
#include "../tipos.h"

#include "bomb.h"
#include "gameConfig.h"
#include "manageTexture.h"
#include "playerView.h"
#include "text.h"

class HUDItem {
public:
    Text texto;
    SDL_Texture* icono;  // Puede ser null
    SDL_Rect icono_rect;

    HUDItem(Text text, SDL_Texture* icono = nullptr, SDL_Rect rect = {})
        : texto(std::move(text)), icono(icono), icono_rect(rect) {}

    void draw(SDL_Renderer& renderer) {
        if (icono) {
            SDL_RenderCopy(&renderer, icono, nullptr, &icono_rect);
        }
        texto.draw(renderer);
    }
};
class HUD {
private:
    InfoGame info_name;
    GameConfig config;
    ManageTexture& texture_manager;
    std::map<TextView, HUDItem> texts;
    PlayerImage player;
    BombImage bomb;
    uint8_t time;
    GameStateImage game_state;
    Object weapon_used;

    PlayerImage jugador_inicial();

    BombImage bomba_inicial();

    GameStateImage estado_juego_inicial();

    void load_text(const TextView& clave, const int& x, const int& y, SDL_Texture* icono = nullptr);

    void load_info(const TextView& clave, const std::string text, Color color_id, TTF_Font* font);


public:
    HUD(GameConfig& config, ManageTexture& manager,const InfoGame& info_game);

    void load(PlayerImage& player, BombImage& bomb, uint8_t time, GameStateImage game_state);
    void update();
    void render(SDL_Renderer& renderer);
};