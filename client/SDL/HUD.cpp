
#include "HUD.h"

#include <string>


HUD::HUD(GameConfig& config, ManageTexture& manager, const InfoGame& info_game):
        info_name(info_game),
        config(config),
        texture_manager(manager),
        texts(),
        player(jugador_inicial()),
        bomb(bomba_inicial()),
        time(0),
        game_state(estado_juego_inicial()),
        weapon_used(Object::GLOCK)

{
    SDL_Texture* icono_vida = texture_manager.get(Object::VIDA);
    SDL_Texture* icono_dinero = texture_manager.get(Object::MONEY);
    SDL_Texture* icono_timer_bomb = texture_manager.get(Object::TIMER_BOMB);
    SDL_Texture* icono_timer = texture_manager.get(Object::TIMER);
    SDL_Texture* icono_bullet = texture_manager.get(Object::BALA);
    SDL_Texture* icono_weapon = texture_manager.get(weapon_used);

    int ancho = config.get_window_width();
    int alto = config.get_window_height();

    int margen_lateral = 30;
    int x_izquierda = margen_lateral + margen_lateral;
    int x_centro = (ancho / 2) - margen_lateral * 3;
    int x_derecha = ancho - margen_lateral - margen_lateral * 1;

    int margen_y = 30;
    int fila1_y = alto - margen_y - 40;
    int fila2_y = alto - margen_y;

    // Texto superior (centrado arriba)
    load_text(TextView::TIME, x_derecha - 80, 20, icono_timer);
    load_text(TextView::BOMB, x_izquierda, 20, icono_timer_bomb);

    // Fila inferior 1
    load_text(TextView::WEAPON, x_izquierda, fila1_y, icono_weapon);
    load_text(TextView::POINTS, x_centro, fila1_y);
    load_text(TextView::MONEY, x_derecha, fila1_y, icono_dinero);

    // Fila inferior 2
    load_text(TextView::HEALTH, x_derecha, fila2_y, icono_vida);
    load_text(TextView::TEAM, x_centro, fila2_y);
    load_text(TextView::AMMO, x_izquierda, fila2_y, icono_bullet);
}

PlayerImage HUD::jugador_inicial() {
    Position pos = {100, 100};
    Position mouse = {110, 110};
    std::vector<WeaponImage> armas;
    SoundImage sonidos;
    armas.emplace_back(WeaponCode::GLOCK, 20, 20, 60);  // Arma básica

    return PlayerImage(1,    // player_id
                       pos,  // position
                       100,  // health
                       0,    // deaths
                       0,    // points
                       0, WeaponCode::NONE, std::move(armas),
                       Team::CT,  // team
                       mouse, Skins(CounterTerroristSkin::GIGN, TerroristSkin::GUERRILLA),
                       std::move(sonidos));
}

BombImage HUD::bomba_inicial() { return BombImage(Position{0, 0}, BombState::DROPPED); }

GameStateImage HUD::estado_juego_inicial() {
    return GameStateImage(GameState::TIME_TO_BUY, 120, 1);  // 2 min de compra, ronda 1
}

void HUD::load_text(const TextView& clave, const int& x, const int& y, SDL_Texture* icono) {
    Text text_obj(texture_manager, clave, x, y);

    SDL_Rect rect_icono = {x - 40, y, 32, 32};  // Ícono a la izquierda del texto
    HUDItem item(text_obj, icono, rect_icono);
    texts.insert({clave, item});
}


void HUD::load_info(const TextView& clave, const std::string text, Color color_id, TTF_Font* font) {

    SDL_Color color = config.get_color(color_id);
    auto it = texts.find(clave);

    if (it != texts.end()) {
        SDL_SetTextureColorMod(it->second.icono, color.r, color.g, color.b);  // Aplica tinte
        SDL_SetTextureAlphaMod(it->second.icono, color.a);
        it->second.texto.updateText(text, font, color);
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

std::string get_bomb_state(BombImage& bomb) {

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
    return bomb_state_str;
}

Object convertir_a_imagen(WeaponCode code) {
    switch (code) {
        case WeaponCode::AK47:
            return Object::AK47;
        case WeaponCode::AWP:
            return Object::AWP;
        case WeaponCode::GLOCK:
            return Object::GLOCK;
        case WeaponCode::KNIFE:
            return Object::SNIKE;
        case WeaponCode::BOMB:
            return Object::BOMB;
        case WeaponCode::M3:
            return Object::M3;
        default:
            throw std::invalid_argument("WeaponCode desconocido");
    }
}

/*
    Aca deberias de hacer 2 funciones.

    Una que encuentre y dibuje el arma equipada //Puede ser como el original y resaltarla con color
    Otra que dibuje las demas en el inventario

*/
void HUD::update() {

    TTF_Font* font = config.get_font_hud();

    if (!player.weapons.empty()) {
        auto weapon = std::find_if(player.weapons.begin(), player.weapons.end(),
                                   [this](const WeaponImage& weapon) {
                                       return weapon.weapon_code == player.equipped_weapon;
                                   });
        if (weapon == player.weapons.end())
            return;  // Exception?
        Object clave = convertir_a_imagen(player.equipped_weapon);
        if (clave != weapon_used) {
            weapon_used = clave;
            texts.at(TextView::WEAPON).icono = texture_manager.get(weapon_used);
        }
        load_info(TextView::WEAPON, get_weapon_str(weapon->weapon_code), Color::AMARILLO, font);
        // Faltan las demas armas aca!
    }
    int balas = 0;
    int inventory_bullets = 0;
    std::string bomb_state_str = get_bomb_state(bomb);
    for (auto weapon: player.weapons) {
        if (weapon.weapon_code == player.equipped_weapon) {
            balas = weapon.current_bullets;
            inventory_bullets = weapon.inventory_bullets;
            break;
        }
    }
    load_info(TextView::BOMB, bomb_state_str, Color::AMARILLO, font);
    load_info(TextView::AMMO, std::to_string(balas) + " / " + std::to_string(inventory_bullets),
              Color::AMARILLO, font);
    load_info(TextView::HEALTH, std::to_string(player.health), Color::AMARILLO, font);
    load_info(TextView::TIME, std::to_string(time), Color::AMARILLO, font);
    load_info(TextView::POINTS, "PUNTOS : " + std::to_string(player.points), Color::AMARILLO, font);
    load_info(TextView::MONEY, std::to_string(player.money), Color::AMARILLO, font);
    load_info(TextView::TEAM, player.team == Team::CT ? "CT" : "TT", Color::AMARILLO, font);
}

void HUD::render(SDL_Renderer& renderer) {
    for (auto& [clave, item]: texts) {
        if (clave == TextView::BOMB && player.team == Team::CT) {
            continue;  // No dibujar el icono de bomba si es CT
        }
        item.draw(renderer);
    }
}
