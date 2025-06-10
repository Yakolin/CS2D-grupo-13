#include "fieldOfView.h"


FieldOfView::FieldOfView(PlayerView& player, Camera& camera, ManageTexture& manager,
                         GameConfig& config_game):
        player(player),
        camera(camera),
        manager(manager),
        lado(config_game.get_window_width() + config_game.get_window_height()),
        texture_fov(nullptr),
        config(config_game) {
    texture_fov = manager.create_stencil(lado, lado, 0.0f, 90.0f);
}


void FieldOfView::draw(SDL_Renderer& renderer) {

    SDL_Rect dstRect;
    dstRect.w = lado;
    dstRect.h = lado;
    dstRect.x = static_cast<int>(player.getXActual()) - camera.getX() - lado / 2;
    dstRect.y = static_cast<int>(player.getYActual()) - camera.getY() - lado / 2;

    SDL_RenderCopyEx(&renderer, texture_fov, nullptr, &dstRect, player.getAnglePlayer(), nullptr,
                     SDL_FLIP_NONE);
}


void FieldOfView::actualizarStencil(const int nuevo_ancho, const int nuevo_alto,
                                    const float apertura) {


    if (texture_fov)
        SDL_DestroyTexture(texture_fov);

    texture_fov = manager.create_stencil(nuevo_ancho, nuevo_alto, 0.0f,
                                         apertura);  // ángulo 0, solo para la forma
}