// camera.h (ya sin incluir playerView.h)

#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include <SDL2/SDL.h>
class Camera {
private:
    SDL_Rect camera;
    int anchoVentana;
    int altoVentana;
    int x;
    int y;

public:
    explicit Camera(const int& ancho, const int& alto);

    void set_viewport_size(const int& nuevoAncho, const int& nuevoAlto);

    int getX();

    int getY();

    void update(const float& row, const float& col, const int& playerWidth, const int& playerHeight,
                const int& mapWidth, const int& mapHeight);

    void setViewportSize(const int& w, const int& h);

    int getW();

    int getH();
};

#endif  // CAMERA_H
