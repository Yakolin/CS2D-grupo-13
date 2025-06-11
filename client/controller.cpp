#include "controller.h"

#define MAX_QUEUE_SIZE 100000

Controller::Controller(Socket&& skt):
        skt(std::move(skt)),
        send_queue(std::make_shared<Queue<std::unique_ptr<InterfaceClientAction>>>(MAX_QUEUE_SIZE)),
        recv_queue(std::make_shared<Queue<GameImage>>(MAX_QUEUE_SIZE)),
        sender(this->skt, this->send_queue),
        receiver(this->skt, this->recv_queue) {
    start();
}

TerroristSkin Controller::toItemTerrorism(const std::string& str) {
    if (str == "Phoenix")
        return TerroristSkin::PHOENIX;
    if (str == "L337 Krew")
        return TerroristSkin::L337_KREW;
    if (str == "Arctic Avenger")
        return TerroristSkin::ARCTIC_AVENGER;
    return TerroristSkin::GUERRILLA;
}
CounterTerroristSkin Controller::toItemCounterTerrorism(const std::string& str) {
    if (str == "Seal Force")
        return CounterTerroristSkin::SEAL;
    if (str == "German GSG-9")
        return CounterTerroristSkin::GSG9;
    if (str == "UK SAS")
        return CounterTerroristSkin::SAS;
    return CounterTerroristSkin::GIGN;
}
void Controller::sender_pos_mouse(int x, int y) {

    int tile_size = 32;
    coordinate_t col = static_cast<coordinate_t>(x / tile_size);
    coordinate_t fil = static_cast<coordinate_t>(y / tile_size);
    std::cout << "Enviando pos del mouse\n";
    std::unique_ptr<InterfaceClientAction> action =
            std::make_unique<ClientSpace::MousePosition>(col, fil);
    send_queue->push(std::move(action));
}

void Controller::sender_equip(EquipType& equip) {
    std::unique_ptr<InterfaceClientAction> action = std::make_unique<ClientSpace::Equip>(equip);
    send_queue->push(std::move(action));
}

void Controller::sender_reload() {
    std::unique_ptr<InterfaceClientAction> action = std::make_unique<ClientSpace::Reload>();
    send_queue->push(std::move(action));
}

void Controller::sender_shoot(int x, int y) {
    coordinate_t x_c = static_cast<coordinate_t>(x);
    coordinate_t y_c = static_cast<coordinate_t>(y);
    std::unique_ptr<InterfaceClientAction> action = std::make_unique<ClientSpace::Shoot>(x_c, y_c);
    send_queue->push(std::move(action));
}

void Controller::sender_buy_weapon(WeaponCode code) {
    std::unique_ptr<InterfaceClientAction> action = std::make_unique<ClientSpace::BuyWeapon>(code);
    send_queue->push(std::move(action));
}
void Controller::sender_defuse() {
    std::unique_ptr<InterfaceClientAction> action = std::make_unique<ClientSpace::DefuseBomb>();
    send_queue->push(std::move(action));
}
void Controller::sender_drop() {
    std::unique_ptr<InterfaceClientAction> action = std::make_unique<ClientSpace::Drop>();
    send_queue->push(std::move(action));
}

void Controller::sender_mov_player(SDL_Keycode key) {
    MoveType mov = MoveType::DOWN;

    if (key == SDLK_UP || key == SDLK_w) {
        mov = MoveType::UP;
        std::cout << "Tecla ARRIBA o W presionada -> mov = UP\n";
    } else if (key == SDLK_LEFT || key == SDLK_a) {
        mov = MoveType::LEFT;
        std::cout << "Tecla IZQUIERDA o A presionada -> mov = LEFT\n";
    } else if (key == SDLK_RIGHT || key == SDLK_d) {
        mov = MoveType::RIGHT;
        std::cout << "Tecla DERECHA o D presionada -> mov = RIGHT\n";
    } else if (key == SDLK_DOWN || key == SDLK_s) {
        mov = MoveType::DOWN;
        std::cout << "Tecla ABAJO o S presionada -> mov = DOWN\n";
    } else {
        std::cout << "Tecla no mapeada presionada: " << SDL_GetKeyName(key) << "\n";
    }

    std::cout << "----------------enviando mov --------------------------\n";
    std::unique_ptr<InterfaceClientAction> action = std::make_unique<ClientSpace::Move>(mov);
    send_queue->push(std::move(action));
    std::cout << "Movimiento enviado (enum como int): " << static_cast<int>(mov) << std::endl;
}


void Controller::start() {

    this->receiver.start();
    this->sender.start();
}
void Controller::stop() {
    this->receiver.stop();
    this->sender.stop();
    this->skt.shutdown(2);
    this->skt.close();
    this->receiver.join();
    this->sender.join();
}
bool Controller::is_valid_weapon_code(WeaponCode code) {
    switch (code) {
        case WeaponCode::BOMB:
        case WeaponCode::AK47:
        case WeaponCode::AWP:
        case WeaponCode::M3:
        case WeaponCode::KNIFE:
        case WeaponCode::GLOCK:
            return true;
        default:
            return false;
    }
}


bool Controller::has_game_image(GameImage& snapshot) {

    if (recv_queue->empty()) {
        return false;
    }
    snapshot = recv_queue->pop();
    //  std::cout << "recibo de la cola\n";
    return true;
}

void Controller::run() {}

Controller::~Controller() {}
