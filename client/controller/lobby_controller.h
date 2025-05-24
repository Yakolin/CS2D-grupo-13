#ifndef LOBBY_CONTROLLER_H
#define LOBBY_CONTROLLER_H

#include "game.h"

/*
Esta clase deberia ser la clase input, es decir, la clase que recibe el socket donde se ejecuta el
lobby, deberia conocer la ventana del lobby y mostrarle informacio basandose en lo que lee del
ClientProtocol, una vez que termina de ejecutarse, de alguna manera deberia salir del while y llamar
al game, internamente tiene un while el game por ende se empezara a ejecutar el game
*/

class LobbyController {
private:
    Game game;

public:
    LobbyController(const char* host, const char* port);
    ~LobbyController();
    void run();  // aca primero ejecutaria el lobby y luego llamaria al game
};

#endif  // !LOBBY_CONTROLLER_H