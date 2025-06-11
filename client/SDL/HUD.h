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
    PlayerImage& player;
    BombImage& bomb;
    uint8_t time;
    GameState& game_state;

    void load_text(const TextView &clave, const int &x, const int &y);

    void load_info(const TextView &clave, const std::string text, Color color_id, TTF_Font *font);

    public:
    HUD(PlayerImage& player,GameConfig& config,ManageTexture& manager, BombImage& bomb, uint8_t time, GameState game_state);


    void update();
    void render(SDL_Renderer& renderer);
};