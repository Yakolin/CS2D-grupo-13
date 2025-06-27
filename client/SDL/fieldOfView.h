#ifndef FIELD_OF_VIEW_H
#define FIELD_OF_VIEW_H

#include "camera.h"
#include "gameConfig.h"
#include "manageTexture.h"
#include "playerView.h"
#include "renderizable.h"
class FieldOfView: public Renderizable {

private:
    PlayerView& player;
    Camera& camera;
    ManageTexture& manager;
    int lado;
    SDL_Texture* texture_fov;
    GameConfig& config;


public:
    explicit FieldOfView(PlayerView& player, Camera& camera, ManageTexture& manager,
                         GameConfig& config_game);


    void draw(SDL_Renderer& renderer) override;
    /**
     * pre:
     * post:
     */
    void actualizarStencil(const int nuevo_ancho, const int nuevo_alto, const float apertura);

    bool is_in_fov(PlayerView& other);
};

#endif  // FIELD_OF_VIEW_H
