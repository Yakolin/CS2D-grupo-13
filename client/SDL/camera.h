// camera.h (ya sin incluir playerView.h)

#ifndef CAMERA_H
#define CAMERA_H

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

    
    void update(const float& row, const float& col, const int& playerWidth, const int& playerHeight,const int& mapWidth, const int& mapHeight);

    int getx() const;
    int gety() const ;

    SDL_Rect* getRect();
};

#endif  // CAMERA_H
