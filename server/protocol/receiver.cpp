#include "receiver.h"

Receiver::Receiver(player_id_t& player_id, Socket& socket,
                   std::shared_ptr<Queue<GameImage>>& send_queue,
                   InterfaceGamesMonitor& games_monitor):
        player_id(player_id),
        protocol(socket),
        recv_queue(nullptr),
        send_queue(send_queue),
        games_monitor(games_monitor),
        closed(false) {}

Receiver::~Receiver() {}


void Receiver::run() {
    this->run_lobby();
    this->run_game();
}

void Receiver::run_lobby() {
    bool in_lobby = true;
    try {
        while (in_lobby && this->should_keep_running()) {
            LobbyCommandType command = this->protocol.read_lobby_command();
            ParseLobbyAction parser(this->player_id, this->protocol, command, this->recv_queue,
                                    this->send_queue, this->games_monitor, in_lobby);
            parser();
        }

    } catch (const ConnectionClosedException& e) {
        std::cout << "The client closed the connection" << std::endl;
        this->closed = true;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error en el lobby: " << e.what() << std::endl;
        this->closed = true;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught." << std::endl;
        this->closed = true;
    }
}

void Receiver::run_game() {
    try {
        while (!this->closed && this->should_keep_running()) {
            PlayerCommandType command = this->protocol.read_player_command();
            std::unique_ptr<ClientAction> action;
            ParsePlayerAction parser(this->player_id, this->protocol, command, action);
            parser();
            if (!this->closed && this->recv_queue) {
                this->recv_queue->push(std::move(action));
            }
        }
    } catch (ClosedQueue& e) {
        this->closed = true;
    } catch (const ConnectionClosedException& e) {
        this->closed = true;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught in receiver."
                  << std::endl;
        this->closed = true;
    }
}

void Receiver::stop() {
    Thread::stop();
    this->closed = true;
}