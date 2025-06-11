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
/*
void Controller::send_buy(WeaponCode code) {
    std::unique_ptr<InterfaceClientAction> action = std::make_unique<ClientSpace::BuyWeapon>(code);
    send_queue->push(std::move(action));
}
*/
void Controller::send_defuse() {  // E
    std::unique_ptr<InterfaceClientAction> action = std::make_unique<ClientSpace::DefuseBomb>();
    send_queue->push(std::move(action));
}

void Controller::send_drop() {  // G
    std::unique_ptr<InterfaceClientAction> action = std::make_unique<ClientSpace::Drop>();
    send_queue->push(std::move(action));
}

void Controller::send_equip(EquipType& equip_type) {  // 1 2 3 4 para cada arma
    std::unique_ptr<InterfaceClientAction> action =
            std::make_unique<ClientSpace::Equip>(equip_type);
    send_queue->push(std::move(action));
}

void Controller::sender_pos_mouse(int x, int y) {

    int tile_size = 32;
    Uint16 col = static_cast<Uint16>(x / tile_size);
    Uint16 fil = static_cast<Uint16>(y / tile_size);

    std::unique_ptr<InterfaceClientAction> action =
            std::make_unique<ClientSpace::MousePosition>(col, fil);
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


bool Controller::has_game_image(GameImage& snapshot) {

    if (recv_queue->empty()) {
        return false;
    }
    snapshot = recv_queue->pop();
    return true;
}

void Controller::run() {}

Controller::~Controller() {}
