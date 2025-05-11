
#include "acceptor.h"

#include <iostream>

Acceptor::Acceptor(const char *port) : socket_acceptor(port), games_monitor(), client_id_counter(0) {}
Acceptor::~Acceptor() {}

void Acceptor::run()
{
    try
    {
        while (this->should_keep_running())
        {
            Socket peer = socket_acceptor.accept();
            this->client_id_counter++;
            clients.emplace(this->client_id_counter, std::make_unique<ClientHandler>(std::move(peer), this->games_monitor));
            this->reap();
            clients[this->client_id_counter]->start();
        }
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << '\n';
    }
    catch (const LibError &e)
    {
    }
}

void Acceptor::stop()
{
    this->socket_acceptor.shutdown(2);
    this->socket_acceptor.close();
    this->clear();
}

void Acceptor::reap()
{
    this->games_monitor.reap();
    auto it = clients.begin();
    while (it != clients.end())
    {
        ClientHandler *c = *it;
        if (!c->is_alive())
        {
            c->join();
            delete c;
            it = clients.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Acceptor::clear()
{ // esta funcion debe ser llamada al final del programa
    this->games_monitor.clear();
    for (auto &[id, client] : clients)
    {
        if (client->is_alive())
        {
            client->stop();
        }
        client->join();
    }
    clients.clear(); // remuevo todos los punteros
}