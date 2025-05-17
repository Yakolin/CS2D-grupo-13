#ifndef MAPVIEW_H
#define MAPVIEW_H
#include <iostream>
#include "tipos.h"
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <iostream>
#include <vector>
#include <SDL_image.h>
#include <map>


class MapView  {

public:
    explicit MapView(const std::vector<std::vector<char>>& mapa, const int& width , const int& height);
    ~MapView();
    void start_game();
    

private:
    SDL_Texture* backgroundTexture;
    SDL_Window* ventana ;
    SDL_Renderer* renderer ;
    std::map<char, std::string> leyenda;
    int width ;
    int height;
    std::vector<std::vector<char>> mapa;
    std::map<char, SDL_Texture*> texturas;
    /*
    pre: el renderer debe haber sido craedo sin problema.
    post: carga una imagen de fondo y la conbierte en textura. //? capaz lo saque no es muy necesario de momento
    */
    bool cargarTexturaFondo(SDL_Renderer* renderer);
    /*
    pre: el render debe ser creado previamente y las rutas ser validas
    post: se guarda en un mapa los SDL_Texture* creados para cada ruta de imagen
    */
    SDL_Texture* add_tiles(const std::string& img );
    /*
    pre:SDL debe estar iniliciado previamente.
    post: inicializa el SDL con soporte para video devuelve true si todo salio bien caso contrario false
    */
    bool initialize_sdl_video();
    /*
    pre:  width y height deben ser mayores que 0.
    post: devuelve true si la unicializacion salio bien de ventana y renderer.
    */
    bool init_render_window();
    /*
    pre: render y texturas deben existir y el mapa no debe estar vacio.
    post:recorre el mapa y dibuja texturas de 32x32 pixeles 
    */
    void complete_map_view();
    /*
    pre: el render debe != nullptr
    post:Carga cada textura imagen segun en una ruta y la guarda en el mapa texturas.
    */
    void load_textures();

};

#endif // MAPVIEW_H