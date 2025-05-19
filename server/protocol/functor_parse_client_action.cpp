#include "functor_parse_client_action.h"

using Server::DefuseBomb;
using Server::Drop;
using Server::ListGames;
using Server::PlantBomb;
using Server::Reload;

ParseLobbyAction::ParseLobbyAction(player_id_t& player_id, ServerProtocol& protocol,
                                   LobbyCommandType& command,
                                   std::unique_ptr<InterfaceLobbyAction>& action):
        Parse(player_id, protocol), command(command), action(action) {}

ParseLobbyAction::~ParseLobbyAction() {}


void ParseLobbyAction::run() {
    switch (this->command) {
        case LobbyCommandType::CREATE_GAME:
            this->action = this->protocol.read_create_game(this->player_id);
            break;
        case LobbyCommandType::JOIN_GAME:
            this->action = this->protocol.read_join_game(this->player_id);
            break;
        case LobbyCommandType::LIST_GAMES:
            this->action = std::make_unique<ListGames>();
            break;
        default:
            throw std::runtime_error("LobbyCommandType no soportado");
    }
}


ParsePlayerAction::ParsePlayerAction(player_id_t& player_id, ServerProtocol& protocol,
                                     PlayerCommandType& command,
                                     std::unique_ptr<InterfacePlayerAction>& action):
        Parse(player_id, protocol), command(command), action(action) {}

ParsePlayerAction::~ParsePlayerAction() {}

void ParsePlayerAction::run() {
    switch (this->command) {
        case PlayerCommandType::MOVE:
            this->action = this->protocol.read_move(this->player_id);
            break;
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
        default:
            throw std::runtime_error("PlayerCommandType no soportado");
    }
}
