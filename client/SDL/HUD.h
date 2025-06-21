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
    SDL_Texture* icono;
    SDL_Rect icono_rect;

    HUDItem(Text text, SDL_Texture* icono = nullptr, SDL_Rect rect = {}):
            texto(std::move(text)), icono(icono), icono_rect(rect) {}

    void draw(SDL_Renderer& renderer) {
        if (icono) {
            SDL_RenderCopy(&renderer, icono, nullptr, &icono_rect);
        }
        texto.draw(renderer);
    }
};
class Mouse {

private:
    TextureInfo info_mouse;
    ItemSprite item_mouse;
    CoordenadaInt pos_mouse;
    GameConfig& config;

public:
    Mouse(GameConfig& config, SDL_Texture* textura):
            info_mouse(), item_mouse({0, 0}), pos_mouse({0, 0}), config(config) {
        info_mouse.textura = textura;
        config.get_dimension(info_mouse.textura, info_mouse.medidas.w, info_mouse.medidas.h);
    }

    void set_pos(const int& x, const int& y) {
        pos_mouse.x = x;
        pos_mouse.y = y;
    }
    void set_item(const int& x, const int& y) {
        item_mouse.col = x;
        item_mouse.fil = y;
    }
    void draw(SDL_Renderer& renderer) {
        int ancho = info_mouse.medidas.w;
        int alto = info_mouse.medidas.h;

        SDL_Rect src = {item_mouse.col * ancho, item_mouse.fil * alto, ancho / 2, alto / 2};
        SDL_Rect dst = {pos_mouse.x, pos_mouse.y, config.get_tile_width(),
                        config.get_tile_height()};
        SDL_RenderCopyEx(&renderer, info_mouse.textura, &src, &dst, 0.0f, nullptr, SDL_FLIP_NONE);
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
    uint16_t time;
    GameStateImage game_state;
    Object weapon_used;
    Mouse mouse;

    PlayerImage jugador_inicial();

    BombImage bomba_inicial();

    GameStateImage estado_juego_inicial();

    void load_text(const TextView& clave, const int& x, const int& y, SDL_Texture* icono = nullptr);

    void load_info(const TextView& clave, const std::string text, Color color_id, TTF_Font* font);
    Mouse init_mouse(ManageTexture& manager, GameConfig& config);

    void load_state_win();

public:
    HUD(GameConfig& config, ManageTexture& manager, const InfoGame& info_game);

    void updateMouseSprite(const CursorContext& context);

    void update_mouse(const int& x, const int& y);
    void load(PlayerImage& player, BombImage& bomb, uint16_t& time, GameStateImage& game_state);
    void update();
    void render(SDL_Renderer& renderer);
};