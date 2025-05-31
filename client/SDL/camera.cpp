#include "camera.h"

Camera::Camera(const int& ancho, const int& alto)
    : camera{0, 0, ancho, alto},
      anchoVentana(ancho),
      altoVentana(alto),
      x(0),
      y(0) {}


void Camera::update(const float& row, const float& col, const int& playerWidth, const int& playerHeight,  const int& mapWidth, const int& mapHeight) {

    camera.x = static_cast<int>(col + playerWidth / 2 - camera.w / 2);
    camera.y = static_cast<int>(row + playerHeight / 2 - camera.h / 2);

    if (camera.x < 0)
        camera.x = 0;
    if (camera.y < 0)
        camera.y = 0;
    if (camera.x > mapWidth - camera.w)
        camera.x = mapWidth - camera.w;
    if (camera.y > mapHeight - camera.h)
        camera.y = mapHeight - camera.h;
    this->x = camera.x;
    this->y = camera.y;
}



int Camera::getx() const {
    return x;
}

int Camera::gety() const {
    return y;
}

SDL_Rect* Camera::getRect() {
    return &camera;
}
