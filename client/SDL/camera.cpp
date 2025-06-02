#include "camera.h"

Camera::Camera(const int& ancho, const int& alto)
    : 
    camera{0, 0, ancho, alto},
    anchoVentana(ancho),
    altoVentana(alto)
    {}


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

void Camera::setViewportSize(const int& w,const int& h) {
    this->camera.w = w;
    this->camera.h = h;
}

void Camera::set_viewport_size(const int& nuevoAncho,const  int& nuevoAlto) {
    this->anchoVentana = nuevoAncho;
    this->altoVentana = nuevoAlto;
}
int Camera::getX(){
    return this->camera.x;
}
int Camera::getY(){
    return this->camera.y;
}
int Camera::getW(){
    return this->camera.w;
}

int Camera::getH(){
    return this->camera.h;
}


SDL_Rect* Camera::getRect() {
    return &camera;
}
