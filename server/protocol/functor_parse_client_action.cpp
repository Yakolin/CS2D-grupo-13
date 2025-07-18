#include "functor_parse_client_action.h"

using ServerSpace::DefuseBomb;
using ServerSpace::Drop;
using ServerSpace::Reload;

ParseLobbyAction::ParseLobbyAction(
        player_id_t& player_id, ServerProtocol& protocol, LobbyCommandType& command,
        std::shared_ptr<Queue<std::unique_ptr<ClientAction>>>& recv_queue,
        std::shared_ptr<Queue<GameImage>>& send_queue, InterfaceGamesMonitor& games_monitor,
        bool& in_lobby):
        ParseAction(player_id, protocol),
        command(command),
        recv_queue(recv_queue),
        send_queue(send_queue),
        games_monitor(games_monitor),
        in_lobby(in_lobby) {}

ParseLobbyAction::~ParseLobbyAction() {}

void ParseLobbyAction::read_ack(const std::string& game_name) {
    Acknowledge ack = this->protocol.read_acknowledge();
    if (ack == Acknowledge::READY) {
        this->games_monitor.player_ready(this->player_id, game_name);
    } else {
        throw std::runtime_error("Error en el lobby: ACK ERROR");
    }
    this->in_lobby = false;
}

void ParseLobbyAction::run() {
    switch (this->command) {
        case LobbyCommandType::CREATE_GAME: {
            CreateGame create_game = this->protocol.read_create_game();
            GameInfo game_info;
            if (this->games_monitor.create_game(this->player_id, create_game, this->recv_queue,
                                                this->send_queue, game_info)) {
                protocol.send_game_info(game_info);
                this->read_ack(create_game.game_name);
            }
            break;
        }
        case LobbyCommandType::JOIN_GAME: {
            JoinGame join_game = this->protocol.read_join_game();
            GameInfo game_info;
            if (this->games_monitor.join_game(this->player_id, join_game, this->recv_queue,
                                              this->send_queue, game_info)) {
                protocol.send_game_info(game_info);
                this->read_ack(join_game.game_name);
            }
            break;
        }
        case LobbyCommandType::LIST_GAMES: {
            std::vector<std::string> list_games = this->games_monitor.list_games();
            ListGame games(list_games);
            this->protocol.send_list_games(games);
            break;
        }
        case LobbyCommandType::EXIT_GAME: {
            this->in_lobby = false;
            break;
        }
        case LobbyCommandType::HELP_GAME:
            // Aquí podrías enviar un mensaje de ayuda al cliente, si es necesario.
            // Por ejemplo, podrías enviar una lista de comandos disponibles.
            break;
        case LobbyCommandType::NONE:
            // Este caso podría ser utilizado para indicar que no se ha recibido un comando válido.
            // Podrías optar por no hacer nada o lanzar una excepción si es necesario.
            break;
        default:
            throw std::runtime_error("LobbyCommandType no soportado");
    }
}

ParsePlayerAction::ParsePlayerAction(player_id_t& player_id, ServerProtocol& protocol,
                                     PlayerCommandType& command,
                                     std::unique_ptr<ClientAction>& action):
        ParseAction(player_id, protocol), command(command), action(action) {}

ParsePlayerAction::~ParsePlayerAction() {}

void ParsePlayerAction::run() {
    switch (this->command) {
        case PlayerCommandType::MOVE:
            this->action = this->protocol.read_move(this->player_id);
            break;
        case PlayerCommandType::BUY_WEAPON:
            this->action = this->protocol.read_buy_weapon(this->player_id);
            break;
        case PlayerCommandType::RELOAD:
            this->action = std::make_unique<Reload>(this->player_id);
            break;
        case PlayerCommandType::SHOOT:
            this->action = this->protocol.read_shoot(this->player_id);
            break;
        case PlayerCommandType::SHOOT_BURST:
            this->action = this->protocol.read_shoot_burst(this->player_id);
            break;
        case PlayerCommandType::DEFUSE_BOMB:
            this->action = std::make_unique<DefuseBomb>(this->player_id);
            break;
        case PlayerCommandType::DROP:
            this->action = std::make_unique<Drop>(this->player_id);
            break;
        case PlayerCommandType::EQUIP:
            this->action = this->protocol.read_equip(this->player_id);
            break;
        case PlayerCommandType::WATCH:
            this->action = this->protocol.read_mouse_position(this->player_id);
            break;
        default:
            throw std::runtime_error("PlayerCommandType no soportado");
    }
}
