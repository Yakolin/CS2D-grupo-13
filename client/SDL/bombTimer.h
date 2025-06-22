#include <SDL_stdinc.h>
#include "../tipos.h"
#include "../soundConfig.h"
#ifndef BOMB_TIMER_H
#define BOMB_TIMER_H

class BombTimer {

    Uint32 tiempo_inicio_ms;
    int duracion_total_s;
    Uint32 ultimo_pip_ms = 0;

public:

    void start(int segundos_restantes) ;

    void update(SoundConfig& sonido);

    float calcular_intervalo_pip(float tiempo_restante);
};
#endif  // BOMB_TIMER_H
