#include "client_handler.h"

ClientHandler::ClientHandler(uint16_t client_id, Socket&& socket, GamesMonitor& games_monitor):
        client_id(client_id),
        socket(std::move(socket)),
        games_monitor(games_monitor),
        protocol(this->socket),
        in_lobby(true) {}

ClientHandler::~ClientHandler() {}

void ClientHandler::run() {
    try {
        while (this->should_keep_running() && in_lobby) {
            LobbyAction action = this->protocol.read_lobby_action();
            std::cout << "accion recibida: " << static_cast<int>(action) << std::endl;
            switch (action) {
                case LobbyAction::CREATE: {
                    std::string game_name = this->protocol.read_name();
                    if (this->games_monitor.create_game(this->client_id, this->socket, game_name)) {
                        this->in_lobby = false;
                    }
                    break;
                }
                case LobbyAction::JOIN: {
                    std::string game_name = this->protocol.read_name();
                    if (this->games_monitor.join_game(this->client_id, this->socket, game_name)) {
                        this->in_lobby = false;
                    }
                    break;
                }
                case LobbyAction::LIST: {
                    std::vector<std::string> game_names = this->games_monitor.list_games();
                    this->protocol.send_games(game_names);
                    break;
                }
            }
        }
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

void ClientHandler::stop() {
    this->socket.shutdown(2);
    this->socket.close();
}