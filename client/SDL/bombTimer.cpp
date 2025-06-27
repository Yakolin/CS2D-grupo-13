#include "bombTimer.h"

#include <algorithm>

void BombTimer::start(int segundos) {
    tiempo_anterior = segundos;
    this->timer_start = true;
}

void BombTimer::update(SoundConfig& sonido, int restante) {
    if (restante == 0 || !timer_start) {
        mostrar_flash = false;
        return;
    }
    Uint32 ahora = SDL_GetTicks();
    Uint32 delta = ahora - ultimo_pip_ms;
    float interval = std::max(10, restante * 100);
    if (delta >= interval) {
        sonido.play_sound(EffectType::PIP, 0);
        ultimo_pip_ms = ahora;
        mostrar_flash = true;
        tiempo_anterior = restante;
        tiempo_ultimo_flash = ahora;
    }
    if (delta < interval)
        mostrar_flash = false;
}
void BombTimer::stop() {
    timer_start = false;
    mostrar_flash = false;
}

bool BombTimer::debe_dibujar_flash() const { return mostrar_flash; }
