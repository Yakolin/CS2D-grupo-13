#include <iostream>

std::pair<int, int> convertir_a_pixeles(int x_log, int y_log, int ancho_px, int alto_px) {
    int x_px = (x_log * ancho_px) / 65536;
    int y_px = (y_log * alto_px) / 65536;
    return {x_px, y_px};
}

int main() {
    // Tamaño de tu pantalla o canvas
    int ancho_pantalla = 544;
    int alto_pantalla = 1216;

    // Coordenadas lógicas recibidas del servidor
    int x_logico = 32768;  // mitad del rango lógico
    int y_logico = 49152;  // tres cuartos del rango lógico

    // Convertir a píxeles
    auto [x_pixel, y_pixel] = convertir_a_pixeles(x_logico, y_logico, ancho_pantalla, alto_pantalla);
    std::cout << "Coordenadas en píxeles: (" << x_pixel << ", " << y_pixel << ")" << std::endl;

    return 0;
}
