#include "manageTexture.h"
const int OFFSET = 40;
ManageTexture::ManageTexture(SDL_Renderer* renderer): renderer(renderer) {
    colores = {{Color::ROJO, {255, 0, 0, 255}},       {Color::VERDE, {0, 255, 0, 255}},
               {Color::AZUL, {0, 0, 255, 255}},       {Color::BLANCO, {255, 255, 255, 255}},
               {Color::NEGRO, {0, 0, 0, 255}},        {Color::AMARILLO, {255, 255, 0, 255}},
               {Color::CIAN, {0, 255, 255, 255}},     {Color::MAGENTA, {255, 0, 255, 255}},
               {Color::GRIS, {128, 128, 128, 255}},   {Color::NARANJA, {255, 165, 0, 255}},
               {Color::VIOLETA, {138, 43, 226, 255}}, {Color::ROSADO, {255, 192, 203, 255}}};


    load(Object::EXPLOSION, "assets/gfx/explosion.png");
    load(Object::BULLET, "assets/gfx/bala.png");

    load_skins_tt(TerroristSkin::PHOENIX, "assets/gfx/terrorist/t2.png");
    load_skins_tt(TerroristSkin::L337_KREW, "assets/gfx/terrorist/t4.png");
    load_skins_tt(TerroristSkin::ARCTIC_AVENGER, "assets/gfx/terrorist/t3.png");
    load_skins_tt(TerroristSkin::GUERRILLA, "assets/gfx/terrorist/t1_1.png");
    load_skins_ct(CounterTerroristSkin::SEAL, "assets/gfx/counterTerrorist/ct2.png");
    load_skins_ct(CounterTerroristSkin::GSG9, "assets/gfx/counterTerrorist/ct4.png");
    load_skins_ct(CounterTerroristSkin::SAS, "assets/gfx/counterTerrorist/ct3.png");
    load_skins_ct(CounterTerroristSkin::GIGN, "assets/gfx/counterTerrorist/ct1.png");
    load_weapons(WeaponCode::BOMB, "assets/gfx/weapons/bomb.png", renderer);
    load_weapons(WeaponCode::AK47, "assets/gfx/weapons/ak47v.png", renderer);
    load_weapons(WeaponCode::AWP, "assets/gfx/weapons/awpv.png", renderer);
    load_weapons(WeaponCode::M3, "assets/gfx/weapons/m3v.png", renderer);
    load_weapons(WeaponCode::KNIFE, "assets/gfx/weapons/knife.png", renderer);
    load_weapons(WeaponCode::GLOCK, "assets/gfx/weapons/glock.png", renderer);
}

void ManageTexture::drawHealthBar(int x, int y, int width, int height, float healthPercent) {
    // Contorno de la barra
    SDL_Rect border = {x, y, width, height};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Color blanco
    SDL_RenderDrawRect(renderer, &border);

    // Barra de vida (relleno)
    SDL_Rect healthBar = {x + 2, y + 2, static_cast<int>((width - 4) * healthPercent), height - 4};
    SDL_SetRenderDrawColor(renderer, 255 * (1 - healthPercent), 255 * healthPercent, 0,
                           255);  // Rojo -> Verde
    SDL_RenderFillRect(renderer, &healthBar);
}


void ManageTexture::render_text(const SDL_Rect& rect, const std::string& text,
                                const SDL_Color& color, TTF_Font* font) {
    if (!font) {
        std::cerr << "Error: font es nullptr - " << TTF_GetError() << std::endl;
        return;
    }

    if (text.empty()) {
        std::cerr << "Advertencia: intentando renderizar texto vacío" << std::endl;
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!surface) {
        std::cerr << "Error renderizando texto: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cerr << "Error creando textura desde superficie: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect textRect = {rect.x + rect.w + 10, rect.y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void ManageTexture::calculate_dimensions(int& width_img, int& height_img, const Object& clave) {
    SDL_Texture* texture = get(clave);
    if (!texture) {
        throw std::runtime_error("No se pudo cargar la textura.");
    }

    if (SDL_QueryTexture(texture, nullptr, nullptr, &width_img, &height_img) != 0) {
        throw std::runtime_error("Error al consultar la textura: " + std::string(SDL_GetError()));
    }
}
std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}
SDL_Rect rect(const int& x, const int& y, const int& w, const int& h) { return {x, y, w, h}; }

SDL_Texture* ManageTexture::reder_menu_texture(
        const std::unordered_map<WeaponCode, ShopItem>& items, const SDL_Rect& menu_rect,
        TTF_Font* font) {


    SDL_Texture* menuTexture = SDL_CreateTexture(
            renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, menu_rect.w, menu_rect.h);
    SDL_SetTextureBlendMode(menuTexture, SDL_BLENDMODE_BLEND);  // Blend mode correcto
    SDL_SetRenderTarget(renderer, menuTexture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);  // Fondo semi-transparente
    SDL_RenderClear(renderer);

    SDL_Rect tileRect = {menu_rect.x, menu_rect.y, 0, 0};

    render_text(tileRect, "- ARMAS", colores.at(Color::ROJO), font);

    for (const auto& item: items) {
        SDL_RenderCopy(renderer, item.second.texture, nullptr, &item.second.destRect);

        SDL_Rect nameRect = item.second.destRect;
        nameRect.x += 10;
        nameRect.y += OFFSET;
        render_text(nameRect, item.second.name, colores.at(Color::BLANCO), font);

        SDL_Rect priceRect = item.second.destRect;
        priceRect.x += 10;
        priceRect.y += OFFSET + 15;
        render_text(priceRect, "$" + std::to_string(item.second.price), colores.at(Color::AMARILLO),
                    font);

        std::vector<std::string> partes = split(item.second.descripcion, ',');
        for (size_t i = 0; i < partes.size(); i++) {
            SDL_Rect descRect = item.second.destRect;
            descRect.x += item.second.destRect.w + 10;
            descRect.y += (i * 25);
            render_text(descRect, partes[i], colores.at(Color::BLANCO), font);
        }
    }

    SDL_SetRenderTarget(renderer, nullptr);
    return menuTexture;
}

void ManageTexture::load(const Object& id, const std::string& filePath) {

    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        throw std::runtime_error("Error cargando imagen: " + std::string(IMG_GetError()));
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        throw std::runtime_error("Error creando textura: " + std::string(SDL_GetError()));
    }

    textures[id] = texture;
}

void ManageTexture::load_skins_tt(const TerroristSkin& id, const std::string& filePath) {

    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        throw std::runtime_error("Error cargando imagen: " + std::string(IMG_GetError()));
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        throw std::runtime_error("Error creando textura: " + std::string(SDL_GetError()));
    }

    texture_skin_tt[id] = texture;
}
void ManageTexture::load_skins_ct(const CounterTerroristSkin& id, const std::string& filePath) {

    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        throw std::runtime_error("Error cargando imagen: " + std::string(IMG_GetError()));
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        throw std::runtime_error("Error creando textura: " + std::string(SDL_GetError()));
    }

    texture_skin_ct[id] = texture;
}

SDL_Texture* ManageTexture::get_texture_ct(const CounterTerroristSkin& id) const {

    auto it = texture_skin_ct.find(id);
    if (it != texture_skin_ct.end()) {
        return it->second;
    }
    return nullptr;
}
SDL_Texture* ManageTexture::get_texture_tt(const TerroristSkin& id) const {

    auto it = texture_skin_tt.find(id);
    if (it != texture_skin_tt.end()) {
        return it->second;
    }
    return nullptr;
}

void ManageTexture::fillTriangle(SDL_Renderer* renderer, int x0, int y0, int x1, int y1, int x2,
                                 int y2) {
    // Ordenar los puntos por Y
    if (y1 < y0) {
        std::swap(y0, y1);
        std::swap(x0, x1);
    }
    if (y2 < y0) {
        std::swap(y0, y2);
        std::swap(x0, x2);
    }
    if (y2 < y1) {
        std::swap(y1, y2);
        std::swap(x1, x2);
    }

    auto drawScanline = [&](int y, int xa, int xb) {
        if (xa > xb)
            std::swap(xa, xb);
        SDL_RenderDrawLine(renderer, xa, y, xb, y);
    };

    for (int y = y0; y <= y2; ++y) {
        bool second_half = y > y1 || y1 == y0;
        int segment_height = second_half ? y2 - y1 : y1 - y0;
        float alpha = (float)(y - y0) / (y2 - y0);
        float beta = (float)(y - (second_half ? y1 : y0)) / segment_height;

        int ax = x0 + (x2 - x0) * alpha;
        int bx = second_half ? x1 + (x2 - x1) * beta : x0 + (x1 - x0) * beta;

        drawScanline(y, ax, bx);
    }
}


std::array<SDL_Point, 4> calculo(const int& lado, const int& angle, const int& apertura) {
    int cx = lado / 2;
    int cy = lado / 2;
    float radio = (lado / 2) * 0.9;  // 90% del máximo
    float angle_rad = angle * M_PI / 180.0f;
    float apertura_rad = apertura * M_PI / 180.0f;

    SDL_Point points[4];
    int x1 = static_cast<int>(cx + radio * cos(angle_rad - apertura_rad / 2));
    int y1 = static_cast<int>(cy + radio * sin(angle_rad - apertura_rad / 2));

    int x2 = static_cast<int>(cx + radio * cos(angle_rad + apertura_rad / 2));
    int y2 = static_cast<int>(cy + radio * sin(angle_rad + apertura_rad / 2));

    points[0] = {cx, cy};
    points[1] = {x1, y1};
    points[2] = {x2, y2};
    points[3] = points[0];

    return {points[0], points[1], points[2], points[3]};
}

SDL_Texture* ManageTexture::create_stencil(const int& ancho, const int& alto, const float& angle,
                                           const float& apertura) {

    int lado = (ancho + alto);
    SDL_Texture* stencil = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                             SDL_TEXTUREACCESS_TARGET, lado, lado);
    if (!stencil) {
        throw std::runtime_error("Error: la textura stencil  no se cargó correctamente.");
    }
    SDL_Texture* old_target = SDL_GetRenderTarget(renderer);
    SDL_SetRenderTarget(renderer, stencil);
    std::array<SDL_Point, 4> points = calculo(lado, angle, apertura);

    int radio_pequeno = 64;                                 // Ajusta este valor al tamaño deseado
    SDL_SetTextureBlendMode(stencil, SDL_BLENDMODE_BLEND);  // vuelve tui textura trasparente

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);  // 128 fondo simi trasparente negro
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    SDL_RenderClear(renderer);

    filledCircleRGBA(renderer, points[0].x, points[0].y, radio_pequeno, 0, 0, 0, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    fillTriangle(renderer, points[0].x, points[0].y, points[1].x, points[1].y, points[2].x,
                 points[2].y);
    SDL_SetRenderTarget(renderer, old_target);

    return stencil;
}


bool ManageTexture::load_weapons(const WeaponCode& id, const std::string& filePath,
                                 SDL_Renderer* renderer) {

    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        std::cerr << "Error cargando imagen: " << IMG_GetError() << std::endl;
        return false;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        std::cerr << "Error creando textura de weapon: " << SDL_GetError() << std::endl;
        return false;
    }

    textures_weapons[id] = texture;
    return true;
}


bool ManageTexture::load_texture_text(const TextView& id, TTF_Font* fuente, SDL_Color& color,
                                      const std::string& text) {


    SDL_Surface* surface = TTF_RenderText_Blended(fuente, text.c_str(), color);
    if (!surface) {
        throw std::runtime_error("Error al crear superficie de texto: " +
                                 std::string(TTF_GetError()));
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        throw std::runtime_error("Error al crear textura de texto: " + std::string(SDL_GetError()));
    }

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);  // para habilitar la transparencia
    SDL_SetTextureAlphaMod(texture, 128);

    TextureData data;
    data.texture = texture;
    data.width = surface->w;
    data.height = surface->h;

    SDL_FreeSurface(surface);
    textures_text[id] = data;
    return true;
}

SDL_Texture* ManageTexture::get_texture_text(const TextView& id) const {

    auto it = textures_text.find(id);
    if (it != textures_text.end()) {
        return it->second.texture;
    }
    return nullptr;
}

SDL_Rect ManageTexture::get_rect(const TextView& id) const {

    auto it_text = textures_text.find(id);
    if (it_text != textures_text.end()) {
        return SDL_Rect{0, 0, it_text->second.width, it_text->second.height};
    }
    return SDL_Rect{0, 0, 0, 0};
}
SDL_Texture* ManageTexture::get_weapon(const WeaponCode& id) const {
    auto it = textures_weapons.find(id);
    // std::cout << "se encontró la textura para Weapon: " << static_cast<int>(id) << std::endl;
    if (it != textures_weapons.end()) {
        return it->second;
    }
    std::cout << "No se encontró la textura para Weapon: " << static_cast<int>(id) << std::endl;
    std::cout << "Claves disponibles: ";
    for (const auto& pair: textures) {
        std::cout << static_cast<int>(pair.first) << " ";
    }
    throw std::runtime_error("Textura no encontrada para el arma solicitada.");
}


SDL_Texture* ManageTexture::get(const Object& id) const {
    auto it = textures.find(id);
    if (it != textures.end()) {
        // std::cout << "se encontró la textura para Object: " << static_cast<int>(id) << std::endl;
        return it->second;
    }
    std::cout << "No se encontró la textura para Object: " << static_cast<int>(id) << std::endl;
    std::cout << "Claves disponibles: ";
    for (const auto& pair: textures) {
        std::cout << static_cast<int>(pair.first) << " ";
    }
    std::cout << std::endl;
    throw std::runtime_error("Textura no encontrada.");
    return nullptr;
}

void ManageTexture::remove(const TextView& id) {
    auto it_tex = textures_text.find(id);
    if (it_tex != textures_text.end()) {
        SDL_DestroyTexture(it_tex->second.texture);
        textures_text.erase(it_tex);
    }
}

void ManageTexture::clear() {
    for (auto& pair: textures) {
        SDL_DestroyTexture(pair.second);
    }
    textures.clear();

    for (auto& pair: textures_text) {
        SDL_DestroyTexture(pair.second.texture);
    }
    textures_text.clear();
}
