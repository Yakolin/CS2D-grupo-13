#include "receiver.h"

Receiver::Receiver(player_id_t& player_id, Socket& socket,
                   std::shared_ptr<Queue<GameImage>>& send_queue, GamesMonitor& games_monitor):
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
            switch (command) {
                case LobbyCommandType::CREATE_GAME: {
                    std::string game_name = protocol.read_create_game();
                    if (this->games_monitor.create_game(this->player_id, game_name,
                                                        this->recv_queue, this->send_queue)) {
                        this->protocol.send_player_id(this->player_id);
                        in_lobby = false;
                    }
                    break;
                }
                case LobbyCommandType::JOIN_GAME: {
                    const std::string game_name = this->protocol.read_join_game();
                    if (this->games_monitor.join_game(this->player_id, game_name, this->recv_queue,
                                                      this->send_queue)) {
                        this->protocol.send_player_id(this->player_id);
                        in_lobby = false;
                    }
                    break;
                }
                case LobbyCommandType::LIST_GAMES: {
                    std::vector<std::string> games_names = games_monitor.list_games();
                    this->protocol.send_list_games(games_names);
                    break;
                }
                default:
                    throw std::runtime_error("Comando invalido");
            }
        }
    } catch (const ConnectionClosedException& e) {}
}


void Receiver::run_game() {
    try {
        while (!this->closed && this->should_keep_running()) {
            PlayerCommandType command = this->protocol.read_player_command();
            std::unique_ptr<IActionToPlayer> action;
            ParsePlayerAction parser(this->player_id, this->protocol, command, action);
            parser();
            if (!this->closed) {
                this->recv_queue->push(std::move(action));
            }
        }

    } catch (ClosedQueue& e) {
        this->closed = true;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught." << std::endl;
        closed = true;
    }
}