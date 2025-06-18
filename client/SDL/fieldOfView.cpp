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
   // int diagonal = std::sqrt(ancho * ancho + alto * alto);

   // this->lado = static_cast<int>(diagonal * 1.5);
    std::cout << "Lado de textura en constructor: " << lado << std::endl;
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
    printf("dstRect: x=%d, y=%d, w=%d, h=%d\n", dstRect.x, dstRect.y, dstRect.w, dstRect.h);
    float angulo = player.getAnglePlayer() - 90.0f;
    SDL_RenderCopyEx(&renderer, texture_fov, nullptr, &dstRect, angulo, nullptr, SDL_FLIP_NONE);
}


void FieldOfView::actualizarStencil(const int nuevo_ancho, const int nuevo_alto,
                                    const float apertura) {
    if (texture_fov)
        SDL_DestroyTexture(texture_fov);

    texture_fov = manager.create_stencil(nuevo_ancho, nuevo_alto, 0.0f,
                                         apertura, config.get_intensity());  // ángulo 0, solo para la forma
}