
#include "acceptor.h"

#include <iostream>

Acceptor::Acceptor(const char* port):
        socket_acceptor(port), games_monitor(), client_id_counter(0) {}
Acceptor::~Acceptor() {}

void Acceptor::run() {
    try {
        while (this->should_keep_running()) {
            std::cout << "esperando conexion..\n";
            Socket peer = socket_acceptor.accept();
            std::cout << "un client se conecto\n";
            this->client_id_counter++;
            try {
                this->reap();
            } catch (const std::runtime_error& e) {
                std::cerr << "Error en el reap" << e.what() << '\n';
            }
            std::cout << "client id: " << this->client_id_counter << '\n';
            clients.emplace(this->client_id_counter,
                            std::make_unique<ClientHandler>(this->client_id_counter,
                                                            std::move(peer), this->games_monitor));
            clients[this->client_id_counter]->start();
            std::cout << "client " << this->client_id_counter << " started\n";
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Error en el acceptor" << e.what() << '\n';
    } catch (const LibError& e) {}
}

bool Acceptor::has_clients() { return !this->clients.empty(); }

void Acceptor::stop() {
    this->socket_acceptor.shutdown(2);
    this->socket_acceptor.close();
    this->clear();
}

void Acceptor::reap() {
    this->games_monitor.reap();
    for (auto it = clients.begin(); it != clients.end();) {
        auto client = it->second.get();
        if (!client->is_alive()) {
            client->join();
            it = clients.erase(it);
        } else {

            ++it;
        }
    }
    std::cout << "client id: " << this->client_id_counter << '\n';
}

void Acceptor::clear() {
    this->games_monitor.clear();
    for (auto& [id, client]: clients) {
        client->stop();
        client->join();
    }
    clients.clear();
}
