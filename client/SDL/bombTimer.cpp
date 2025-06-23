#include "bombTimer.h"

#include <algorithm>

void BombTimer::start(int segundos_restantes) {
    duracion_total_s = segundos_restantes;
    tiempo_inicio_ms = SDL_GetTicks();
    ultimo_pip_ms = 0;
    mostrar_flash = false;
    tiempo_ultimo_flash = 0;
}

void BombTimer::update(SoundConfig& sonido) {
    Uint32 ahora = SDL_GetTicks();
    Uint32 tiempo_pasado_ms = ahora - tiempo_inicio_ms;
    float tiempo_restante = duracion_total_s - (tiempo_pasado_ms / 1000.0f);

    if (tiempo_restante <= 0)
        return;

    float intervalo = calcular_intervalo_pip(tiempo_restante);
    Uint32 intervalo_ms = static_cast<Uint32>(intervalo * 1000);

    if (ahora - ultimo_pip_ms >= intervalo_ms) {
        sonido.play_sound(EffectType::PIP, 0);
        ultimo_pip_ms = ahora;

        mostrar_flash = true;
        tiempo_ultimo_flash = ahora;
    }
    if (mostrar_flash && ahora - tiempo_ultimo_flash >= tiempo_flash_ms) {
        mostrar_flash = false;
    }
}

float BombTimer::calcular_intervalo_pip(float tiempo_restante) const {
    float intervalo = (tiempo_restante / duracion_total_s) * 2.0f;
    return std::max(0.4f, intervalo);
}

bool BombTimer::debe_dibujar_flash() const { return mostrar_flash; }
