#include "functor_parse_client_action.h"

using ServerSpace::DefuseBomb;
using ServerSpace::Drop;
using ServerSpace::PlantBomb;
using ServerSpace::Reload;

ParsePlayerAction::ParsePlayerAction(player_id_t& player_id, ServerProtocol& protocol,
                                     PlayerCommandType& command,
                                     std::unique_ptr<InterfacePlayerAction>& action):
        player_id(player_id), protocol(protocol), command(command), action(action) {}

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
