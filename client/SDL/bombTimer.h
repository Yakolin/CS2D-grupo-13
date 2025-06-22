#pragma once

#include <SDL2/SDL.h>
#include "../soundConfig.h"

class BombTimer {
private:
    Uint32 tiempo_inicio_ms = 0;
    int duracion_total_s = 0;
    Uint32 ultimo_pip_ms = 0;

    bool mostrar_flash = false;
    Uint32 tiempo_flash_ms = 100; 
    Uint32 tiempo_ultimo_flash = 0;

public:
    void start(int segundos_restantes);
    void update(SoundConfig& sonido);
    bool debe_dibujar_flash() const;

private:
    float calcular_intervalo_pip(float tiempo_restante) const;
};
