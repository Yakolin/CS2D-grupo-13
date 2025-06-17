
#include "HUD.h"

#include <string>

HUD::HUD(GameConfig& config, ManageTexture& manager,const InfoGame& info_game):
        info_name(info_game),
        config(config),
        texture_manager(manager),
        texts(),
        player(jugador_inicial()),
        bomb(bomba_inicial()),
        time(0),
        game_state(estado_juego_inicial())

{
    load_text(TextView::TIME, config.get_window_width() / 2, 20);
    int ancho = config.get_window_width();
    int alto = config.get_window_height();
    int margen_y = 30;
    int espacio = 200;  // espacio fijo entre columnas

    int fila1_y = alto - margen_y - 40;
    int fila2_y = alto - margen_y;

    load_text(TextView::TIME, ancho / 2, 20);

    // Fila 1 (3 elementos)
    load_text(TextView::AMMO, espacio * 1, fila1_y);
    load_text(TextView::POINTS, espacio * 2, fila1_y);
    load_text(TextView::MONEY, espacio * 2, fila1_y);
    load_text(TextView::HEALTH, espacio * 3, fila1_y);

    // Fila 2 (4 elementos)
    load_text(TextView::BOMB, espacio * 1, fila2_y);
    load_text(TextView::TEAM, espacio * 2, fila2_y);
    load_text(TextView::WEAPON, espacio * 3, fila2_y);
    load_text(TextView::BULLETS, espacio * 4, fila2_y);
}

PlayerImage HUD::jugador_inicial() {
    Position pos = {100, 100};
    Position mouse = {110, 110};
    std::vector<WeaponImage> armas;
    armas.emplace_back(WeaponCode::GLOCK, 20, 20, 60);  // Arma básica

    return PlayerImage(1,    // player_id
                       pos,  // position
                       100,  // health
                       0,    // points
                       0, WeaponCode::NONE, std::move(armas),
                       Team::CT,  // team
                       mouse, Skins(CounterTerroristSkin::GIGN, TerroristSkin::GUERRILLA));
}


BombImage HUD::bomba_inicial() { return BombImage(Position{0, 0}, BombState::DROPPED); }

GameStateImage HUD::estado_juego_inicial() {
    return GameStateImage(GameState::TIME_TO_BUY, 120, 1);  // 2 min de compra, ronda 1
}


void HUD::load_text(const TextView& clave, const int& x, const int& y) {
    Text item(texture_manager, clave, x, y);
    texts.insert({clave, item});
}
void HUD::load_info(const TextView& clave, const std::string text, Color color_id, TTF_Font* font) {

    SDL_Color color = config.get_color(color_id);
    auto it = texts.find(clave);
    if (it != texts.end()) {
        it->second.updateText(text, font, color);
    } else {
        std::cerr << "Clave no encontrada en texts: " << static_cast<int>(clave) << std::endl;
    }
}

void HUD::load(PlayerImage& player, BombImage& bomb, uint8_t time, GameStateImage game_state) {
    this->player = player;
    this->bomb = bomb;
    this->game_state = game_state;
    this->time = time;
    update();
}
std::string get_weapon_str(WeaponCode weapon) {
    switch (weapon) {
        case WeaponCode::GLOCK:
            return "GLOCK";
        case WeaponCode::AK47:
            return "AK47";
        case WeaponCode::M3:
            return "M3";
        case WeaponCode::AWP:
            return "AWP";
        case WeaponCode::KNIFE:
            return "KNIFE";
        case WeaponCode::BOMB:
            return "BOMB";
        case WeaponCode::NONE:
            return "NONE";
        default:
            return "UNKNOWN";
    }
}
/*
    Aca deberias de hacer 2 funciones.

    Una que encuentre y dibuje el arma equipada //Puede ser como el original y resaltarla con color
    Otra que dibuje las demas en el inventario

*/
void HUD::update() {

    TTF_Font* font = config.get_font_game();

    if (!player.weapons.empty()) {
        auto weapon = std::find_if(player.weapons.begin(), player.weapons.end(),
                                   [this](const WeaponImage& weapon) {
                                       return weapon.weapon_code == player.equipped_weapon;
                                   });
        if (weapon == player.weapons.end())
            return;  // Exception?
        // Esto es el arma primaria, puede ser NONE, debe ser la ACTUAL
        load_info(TextView::WEAPON, get_weapon_str(weapon->weapon_code), Color::NEGRO,
                  font);  // Quizas una imagen
        load_info(TextView::BULLETS,
                  std::to_string(weapon->current_bullets) + "/" + std::to_string(weapon->magazine),
                  Color::AZUL, font);
        // Faltan las demas armas aca!
    }
    // Esto deberia de ser algo que quiza no deberia estar aca?
    std::string bomb_state_str;
    switch (bomb.state) {
        case BombState::EQUIPED:
            bomb_state_str = " Bomba: EQUIPADA";
            break;
        case BombState::DROPPED:
            bomb_state_str = " Bomba: EN SUELO";
            break;
        case BombState::ACTIVATED:
            bomb_state_str = " Bomba: ACTIVADA";
            break;
        case BombState::DESACTIVATED:
            bomb_state_str = " Bomba: DESACTIVADA";
            break;
        case BombState::EXPLOTED:
            bomb_state_str = " Bomba: EXPLOTÓ";
            break;
        default:
            bomb_state_str = " Bomba: ???";
            break;
    }

    load_info(TextView::BOMB, bomb_state_str, Color::NEGRO, font);
    load_info(TextView::HEALTH, "+ " + std::to_string(player.health), Color::NEGRO, font);
    // texture_manager.drawHealthBar(20,20,100,10,0.75f);
    load_info(TextView::TIME, "Reloj" + std::to_string(time), Color::AMARILLO, font);
    load_info(TextView::POINTS, "- PUNTOS : " + std::to_string(player.points), Color::AMARILLO,
              font);
    // load_info(TextView::MONEY, "$ " + std::to_string(player.points))
    load_info(TextView::TEAM, player.team == Team::CT ? "Counter Terrorist" : "Terrorist",
              Color::NEGRO, font);
}

void HUD::render(SDL_Renderer& renderer) {
    for (auto& text: texts) {
        text.second.draw(renderer);
    }
}