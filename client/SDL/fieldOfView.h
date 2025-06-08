#ifndef  FIELDOFDVIEW_H
#define FIELDOFVIEW_H
#include "renderizable.h"
#include "gameConfig.h"
#include "manageTexture.h"
#include "camera.h"
#include "playerView.h"
class FieldOfView: public Renderizable {

private:
    PlayerView& player;
    Camera& camera;
    ManageTexture& manager;
    int lado;
    SDL_Texture* texture_fov;
    GameConfig& config;


public:
    explicit FieldOfView(PlayerView& player, Camera& camera,ManageTexture& manager,GameConfig& config_game);


    void draw(SDL_Renderer& renderer) override ;
    /** 
     * pre: 
     * post:
     */
    void actualizarStencil( const int nuevo_ancho, const int nuevo_alto,const  float apertura);
};


#endif // FIELDOFVIEW_H