#include "functor_parse_client_action.h"
/*
using ServerSpace::DefuseBomb;
using ServerSpace::Drop;
using ServerSpace::PlantBomb;
using ServerSpace::Reload;
*/

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

void ParseLobbyAction::run() {
    switch (this->command) {
        case LobbyCommandType::CREATE_GAME: {
            std::string game_name = this->protocol.read_create_game();
            GameInfo game_info;
            if (this->games_monitor.create_game(this->player_id, game_name, this->recv_queue,
                                                this->send_queue, game_info)) {
                protocol.send_game_info(game_info);
                this->in_lobby = false;
            }
            break;
        }
        case LobbyCommandType::JOIN_GAME: {
            std::string game_name = this->protocol.read_join_game();
            GameInfo game_info;
            if (this->games_monitor.join_game(this->player_id, game_name, this->recv_queue,
                                              this->send_queue, game_info)) {
                protocol.send_game_info(game_info);
                this->in_lobby = false;
            }
            break;
        }
        case LobbyCommandType::LIST_GAMES: {
            std::vector<std::string> list_games = this->games_monitor.list_games();
            this->protocol.send_list_games(list_games);
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
            /*
            case PlayerCommandType::BUY_WEAPON:
            this->action = this->protocol.read_buy_weapon(this->player_id);
            break;
            case PlayerCommandType::BUY_AMMO:
                this->action = this->protocol.read_buy_ammo(this->player_id);
                break;
            case PlayerCommandType::RELOAD:
            this->action = std::make_unique<Reload>(this->player_id);
                break;
                case PlayerCommandType::SHOOT:
                this->action = this->protocol.read_shoot(this->player_id);
                break;
                case PlayerCommandType::PLANT_BOMB:
                this->action = std::make_unique<PlantBomb>(this->player_id);
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
                */
        default:
            throw std::runtime_error("PlayerCommandType no soportado");
    }
}