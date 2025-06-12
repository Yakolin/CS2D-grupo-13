#include "shopping.h"

Shopping::Shopping(Camera& camera_receiver, ManageTexture& manejador, GameConfig& config):
        config(config),
        camera(camera_receiver),
        manejador(manejador),
        items(),
        selectedIndex(),
        rect_shop(),
        activa(false),
        texture_menu(nullptr),
        weapon_selec(WeaponCode::NONE) {}
void Shopping::desactivate_shop() { activa = false; }

void Shopping::code_to_info_weapon(const WeaponCode& code, std::string& name,
                                   std::string& description) {
    switch (code) {
        case WeaponCode::AK47: {
            name = "AK47";
            description = "- Dispara ráfagas de 3 balas, - Mantener click: ráfagas cada 0.4s, -";
            break;
        }
        case WeaponCode::M3: {
            name = "M3";
            description = "- Daño en área en forma de cono, - Menor alcance, "
                          "- Disparo único por click, - Daño muy alto a corta distancia";
            break;
        }

        case WeaponCode::AWP: {
            name = "AWP";
            description = "- Mayor alcance, - Daño máximo, - No afectado por distancia, "
                          "- Retardo alto entre disparos";
            break;
        }
        default:
            std::cerr << "Cant handle the waepon code\n";
            break;
    }
}

void Shopping::load_items(const WeaponInfo& info, const SDL_Rect& destRect) {
    ShopItem new_item;
    new_item.texture = manejador.get_weapon(info.code);
    new_item.price = info.price;
    code_to_info_weapon(info.code, new_item.name, new_item.descripcion);
    new_item.destRect = destRect;
    items.insert({info.code, new_item});
}
void Shopping::set_weapons_purchasables(const std::vector<WeaponInfo>& weapons_purchasables) {
    int window_width = config.get_window_width();
    int window_height = config.get_window_height();

    rect_shop.w = (window_width * 0.8);
    rect_shop.h = (window_height * 0.8);
    rect_shop.x = camera.getX() + 50;
    rect_shop.y = camera.getY() + 50;

    int item_width = 90, item_height = 90, padding = 10;
    int i = 0;
    for (const WeaponInfo& weapon: weapons_purchasables) {
        SDL_Rect destRect;
        destRect.x = rect_shop.x + padding;
        destRect.y = rect_shop.y + padding + i * (item_height + padding);
        destRect.w = item_width;
        destRect.h = item_height;
        load_items(weapon, destRect);
        ++i;
    }
    texture_menu = manejador.reder_menu_texture(items, rect_shop, config.get_font_menu());
}

WeaponCode Shopping::get_wepon_selec() { return weapon_selec; }

void Shopping::activate_shop() { activa = !activa; }

bool Shopping::get_activa() const { return activa; }

WeaponCode Shopping::calculate_selection(const int& mouse_x, const int& mouse_y) {

    for (const auto& item: items) {
        if ((mouse_x >= item.second.destRect.x &&
             mouse_x <= item.second.destRect.x + item.second.destRect.w) &&
            (mouse_y >= item.second.destRect.y &&
             mouse_y <= item.second.destRect.y + item.second.destRect.h)) {
            std::cout << "click EN  " << item.second.name << std::endl;
            WeaponCode code = static_cast<WeaponCode>(item.first);
            return code;
        }
    }
    return WeaponCode::NONE;
}

void Shopping::draw(SDL_Renderer& renderer) {

    if (!texture_menu) {
        std::cerr << "ERROR: texture_menu es nullptr" << std::endl;
        return;
    }

    SDL_RenderCopy(&renderer, texture_menu, nullptr, &rect_shop);
}

Shopping::~Shopping() {}
