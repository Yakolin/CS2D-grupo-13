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
        weapon_selec(WeaponCode::NONE) {

    std::vector<WeaponData> weaponVector = {
            {WeaponCode::AWP, "AWP", 2100,
             "- Mayor  alcance  Daño  maximo ,- No  afectado  por  distancia ,- Retardo  alto  "
             "entre  disparos "},
            {WeaponCode::AK47, "AK47", 2000,
             "- Dispara  ráfagas  de  3 balas ,- Mantener  click:  Rafagas  cada  0.4 balas/seg,- "
             "Daño  menor  que pistola "},
            {WeaponCode::M3, "M3", 200,
             "- Daño  en  area  en  forma  de  cono  ,- Menor  alcance ,- Disparo  unico  por  "
             "click ,- Daño  muy alto  a  corta  distancia "}};

    update(weaponVector);
    texture_menu = manejador.reder_menu_texture(items, rect_shop, config.get_font_menu());
}
WeaponCode Shopping::get_wepon_selec() { return weapon_selec; }

void Shopping::activate_shop() { activa = !activa; }
bool Shopping::get_activa() const { return activa; }

void Shopping::load_items(const WeaponCode& clave, const std::string& name, const int& price,
                          const SDL_Rect& destRect, const std::string& descripcion) {
    ShopItem new_item;
    new_item.texture = manejador.get_weapon(clave);
    new_item.price = price;
    new_item.name = name;
    new_item.destRect = destRect;
    new_item.descripcion = descripcion;
    items.insert({clave, new_item});
}

void Shopping::update(const std::vector<WeaponData>& data) {

    int window_width = config.get_window_width();
    int window_height = config.get_window_height();

    rect_shop.w = (window_width * 0.8);
    rect_shop.h = (window_height * 0.8);
    rect_shop.x = camera.getX() + 50;
    rect_shop.y = camera.getY() + 50;

    int item_width = 90, item_height = 90, padding = 10;
    int i = 0;

    for (WeaponData weapon_data: data) {
        SDL_Rect destRect;
        destRect.x = rect_shop.x + padding;
        destRect.y = rect_shop.y + padding + i * (item_height + padding);
        destRect.w = item_width;
        destRect.h = item_height;
        load_items(weapon_data.clave, weapon_data.name, weapon_data.price, destRect,
                   weapon_data.descripcion);
        ++i;
    }
}
WeaponCode Shopping::calculate_selection(const int& mouse_x, const int& mouse_y) {

    for (const auto& item: items) {
        if ((mouse_x >= item.second.destRect.x &&
             mouse_x <= item.second.destRect.x + item.second.destRect.w) &&
            (mouse_y >= item.second.destRect.y &&
             mouse_y <= item.second.destRect.y + item.second.destRect.h)) {
            std::cout << "click EN  " << item.second.name << std::endl;
            WeaponCode code = static_cast<WeaponCode>(item.first);
            return item.first;
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