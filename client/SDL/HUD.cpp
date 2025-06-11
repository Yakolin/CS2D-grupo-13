
#include "HUD.h"
#include <string>

HUD::HUD(PlayerImage& player,GameConfig& config,ManageTexture& manager,BombImage& bomb, uint8_t time, GameState game_state): 
    config(config),
    texture_manager(manager),
    texts(),
    player(player),
    bomb(bomb),
    time(55),
    game_state(game_state)

{
    load_text( TextView::TIME, config.get_window_width()/2, 20);
    int ancho = config.get_window_width();
    int alto = config.get_window_height();
    int margen_y = 30;
    int espacio = 200;  // espacio fijo entre columnas

    int fila1_y = alto - margen_y - 40;
    int fila2_y = alto - margen_y;

    load_text(TextView::TIME, ancho / 2, 20);

    // Fila 1 (3 elementos)
    load_text(TextView::AMMO,   espacio * 1, fila1_y);
    load_text(TextView::POINTS, espacio * 2, fila1_y);
    load_text(TextView::HEALTH, espacio * 3, fila1_y);

    // Fila 2 (4 elementos)
    load_text(TextView::BOMB,    espacio * 1, fila2_y);
    load_text(TextView::TEAM,    espacio * 2, fila2_y);
    load_text(TextView::WEAPON,  espacio * 3, fila2_y);
    load_text(TextView::BULLETS, espacio * 4, fila2_y);

    update();
}

void HUD::load_text(const TextView& clave,const int& x,const int& y ){
    Text item(texture_manager,clave,x,y);
    texts.insert({clave,item});

}
void HUD::load_info( const TextView& clave, const std::string text,Color color_id,TTF_Font* font){
    
    SDL_Color color = config.get_color(color_id);
    auto it = texts.find(clave);
    if (it != texts.end()) {
        it->second.updateText(text, font, color);
    } else {
        std::cerr << "Clave no encontrada en texts: " << static_cast<int>(clave) << std::endl;
    }

}


std::string get_weapon_str(WeaponCode weapon) {
    switch (weapon) {
        case WeaponCode::GLOCK: return "GLOCK";
        case WeaponCode::AK47: return "AK47";
        case WeaponCode::M3: return "M3";
        case WeaponCode::AWP: return "AWP";
        case WeaponCode::KNIFE: return "KNIFE";
        case WeaponCode::BOMB: return "BOMB";
        case WeaponCode::NONE: return "NONE";
        default: return "UNKNOWN";
    }
}
// actualiza si los valores 
void HUD::update() {

    TTF_Font* font = config.get_font_menu();
    const WeaponImage& weapon = player.weapons[0];  // arma actual
    if (!player.weapons.empty()) {
        load_info(TextView::BULLETS,"- BALA: " + std::to_string(weapon.current_bullets) +"/" + std::to_string(weapon.magazine),Color::AZUL,font);
    } else {
        load_info(TextView::BULLETS,"- SIN BALAS " ,Color::NEGRO,font);
    }
    load_info(TextView::WEAPON,"- WEAPON: "+ get_weapon_str(weapon.weapon_code),Color::NEGRO,font);

    std::string bomb_state_str;
    switch (bomb.state) {
        case BombState::EQUIPED: bomb_state_str = " Bomba: EQUIPADA"; break;
        case BombState::DROPPED: bomb_state_str = " Bomba: EN SUELO"; break;
        case BombState::ACTIVATED: bomb_state_str = " Bomba: ACTIVADA"; break;
        case BombState::DESACTIVATED: bomb_state_str = " Bomba: DESACTIVADA"; break;
        case BombState::EXPLOTED: bomb_state_str = " Bomba: EXPLOTÓ"; break;
        default: bomb_state_str = " Bomba: ???"; break;
    }
    load_info(TextView::BOMB,bomb_state_str,Color::NEGRO,font);
    load_info(TextView::HEALTH,"- VIDA: " + std::to_string(player.health),Color::NEGRO,font);
    //texture_manager.drawHealthBar(20,20,100,10,0.75f);
    load_info(TextView::TIME,"- TIEMPO : " + std::to_string(time), Color::NEGRO,font);
    load_info(TextView::POINTS,"- PUNTOS : " + std::to_string(player.points), Color::NEGRO,font);
    load_info(TextView::TEAM,player.team == Team::CT ? "Equipo: CT" : "Equipo: TT",Color::NEGRO ,font);
}

void HUD::render(SDL_Renderer& renderer) {
    for ( auto& text : texts) {
        text.second.draw(renderer);   
    }
}

