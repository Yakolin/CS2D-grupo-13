#include "fieldOfView.h"


FieldOfView::FieldOfView(PlayerView& player, Camera& camera, ManageTexture& manager,
                         GameConfig& config_game):
        player(player),
        camera(camera),
        manager(manager),
        lado(2000),
        texture_fov(nullptr),
        config(config_game) {
    int ancho= config.get_window_width();
    int alto = config.get_window_height();
    texture_fov = manager.create_stencil(ancho, alto, 0.0f, 90.0f ,config.get_intensity());
}


void FieldOfView::draw(SDL_Renderer& renderer) {

    SDL_Rect dstRect;
    dstRect.w = lado;
    dstRect.h = lado;
    /*
        Aca vean que le sume un 10, esto es un offset porque el player
        al parecer no es el centro centro de la pantalla
    */
    dstRect.x = static_cast<int>(player.getXActual()) - camera.getX() - (lado / 2) + 15;
    dstRect.y = static_cast<int>(player.getYActual()) - camera.getY() - (lado / 2) + 10;
    float angulo = player.getAnglePlayer() - 90.0f;
    SDL_RenderCopyEx(&renderer, texture_fov, nullptr, &dstRect, angulo, nullptr, SDL_FLIP_NONE);
}


bool FieldOfView::is_in_fov(const PlayerView& other) {
    
    float x1 = player.getXActual();
    float y1 = player.getYActual();

    float x2 = other.getXActual();
    float y2 = other.getYActual();

    float dx = x2 - x1;
    float dy = y2 - y1;

    float player_angle = player.getAnglePlayer();  // in degrees
    float angle_to_other = std::atan2(dy, dx) * 180.0f / M_PI;

    float angle_diff = std::fmod((angle_to_other - player_angle + 360.0f), 360.0f);
    if (angle_diff < 180.0f) angle_diff -= 360.0f;

    float fov_half_angle = 90.0f / 2.0f;  // 45° to each side
    return std::abs(angle_diff) <= fov_half_angle;
}

