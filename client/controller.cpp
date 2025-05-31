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

void Controller::sender_pos_mouse(int x, int y) {
    int tile_size = 32;  // tamaño en pixeles de cada bloque del mapa

    int col = x / tile_size;  // columna en la matriz
    int fil = y / tile_size;  // fila en la matriz
    ///... resto de codigo
    std::cout << "Fila: " << fil << ", Columna: " << col << std::endl;
}
void Controller::sender_mov_player(SDL_Keycode key) {

    MoveType mov = MoveType::DOWN;
    if (key == SDLK_UP || key == SDLK_w) {
        mov = MoveType::DOWN;  // Polaridad YA cambiada!
    } else if (key == SDLK_LEFT || key == SDLK_a) {
        mov = MoveType::LEFT;
    } else if (key == SDLK_RIGHT || key == SDLK_d) {
        mov = MoveType::RIGHT;
    } else if (key == SDLK_DOWN || key == SDLK_s) {
        mov = MoveType::UP;
    }

    std::unique_ptr<InterfaceClientAction> action = std::make_unique<ClientSpace::Move>(mov);
    send_queue->push(std::move(action));
    std::cout << static_cast<int>(mov) << std::endl;
}

void Controller::start() {

    this->receiver.start();
    this->sender.start();
}
void Controller::stop() {

    this->receiver.stop();
    this->sender.stop();
    this->receiver.join();
    this->sender.join();
    this->skt.shutdown(2);
    this->skt.close();
}
Position Controller::recibir() {
    GameImage image = recv_queue->pop();
    std::cout << ">>> Estado actual del juego:\n";
    float x_relativo = 0;
    float y_relativo = 0;


    for (size_t i = 0; i < image.players_images.size(); i++) {
        PlayerImage p = image.players_images[i];
        std::cout << "Jugador ID: " << p.player_id << " | Posición: (" << p.position.x << ", "
                  << p.position.y << ")"
                  << " | Vida: " << static_cast<int>(p.health)
                  << " | Puntos: " << static_cast<int>(p.points) << std::endl;
        x_relativo = p.position.x;
        y_relativo = p.position.y;
        std::cout << "------------------------------------------\n ";

        std::cout << "Posición relativa del jugador: (" << x_relativo << ", " << y_relativo << ")"
                  << std::endl;
    }
    return Position(x_relativo, y_relativo);
}
void Controller::run() {}

Controller::~Controller() {
    std::unique_ptr<InterfaceClientAction> action;
    while (this->send_queue->try_pop(action)) {}
}
