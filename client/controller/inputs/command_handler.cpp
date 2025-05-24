#include "command_handler.h"

CommandHandler::CommandHandler(shared_ptr<Queue<GameImage>>& send_queue, Socket& skt):
        send_queue(send_queue), protocol(skt) {}

CommandHandler::~CommandHandler() {}

void CommandHandler::handle_input(
        std::unique_ptr<InterfaceClientAction>&
                action) {  // deberia hacer algo como convertir eventos en objetos segun sea el caso
}

void CommandHandler::run() {
    std::unique_ptr<InterfaceClientAction> action = std::make_unique<InterfaceClientAction>();
    this->handle_input(action);
    if (action) {
        this->send_queue->push(std::move(action));
    }
}