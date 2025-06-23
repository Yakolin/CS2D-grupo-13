#include "controller.h"

#define MAX_QUEUE_SIZE 100000
const int SIZE_TILES = 32;

Controller::Controller(Socket& skt):
        skt(skt),
        send_queue(std::make_shared<Queue<std::unique_ptr<InterfaceClientAction>>>(MAX_QUEUE_SIZE)),
        recv_queue(std::make_shared<Queue<GameImage>>(MAX_QUEUE_SIZE)),
        sender(this->skt, this->send_queue),
        receiver(this->skt, this->recv_queue) {}

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

    coordinate_t col = static_cast<coordinate_t>(x / SIZE_TILES);
    coordinate_t fil = static_cast<coordinate_t>(y / SIZE_TILES);
    std::unique_ptr<InterfaceClientAction> action =
            std::make_unique<ClientSpace::MousePosition>(col, fil);
    send_queue->push(std::move(action));
}

void Controller::sender_equip(EquipType equip) {

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

void Controller::sender_shoot_burst(int x, int y) {

    coordinate_t x_c = static_cast<coordinate_t>(x);
    coordinate_t y_c = static_cast<coordinate_t>(y);
    std::unique_ptr<InterfaceClientAction> action =
            std::make_unique<ClientSpace::ShootBurst>(x_c, y_c);
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


void Controller::sender_move(MoveType move) {
    std::unique_ptr<InterfaceClientAction> action = std::make_unique<ClientSpace::Move>(move);
    send_queue->push(std::move(action));
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
bool Controller::has_game_image(GameImage& snapshot) { return this->recv_queue->try_pop(snapshot); }


Controller::~Controller() {}
