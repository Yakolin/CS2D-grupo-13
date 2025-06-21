#ifndef GAMECONFIG_H
#define GAMECONFIG_H
#include <fstream>
#include <iostream>
#include <string>
#include "../tipos.h"
#include <unordered_map>
#include <vector>
#include <SDL2/SDL.h>
#include <yaml-cpp/yaml.h>
#include "../soundConfig.h"
#include <SDL2/SDL_ttf.h>
#include <unordered_map>
class GameConfig {
    
private:
    int window_width;
    int window_height;
    int tile_width;
    int tile_height;
    int viewport_width;
    int viewport_height;
    TTF_Font* font_menu;
    TTF_Font* font_game;
    TTF_Font* font_hud;
    std::unordered_map<Color, SDL_Color> colores;
    int intensity;
    std::unordered_map<ColorTranslucent, SDL_Color> translucent_colors;
    
    
    void load(const std::string& file_path);

    void load_font(const std::string& route, TTF_Font*& font, const int& size);


public:
    GameConfig();


    void get_dimension(SDL_Texture* texture_player, int& width_img, int& height_img);

    SDL_Color get_color(const Color& clave);

    int get_window_width() const;

    int get_window_height() const;


    int get_tile_width() const;


    int get_tile_height() const;


    int get_viewpost_height() const;


    int get_viewpost_width() const;


    int get_size_font() const;


    std::string get_route_font() const;

    int get_intensity();

    std::vector<std::vector<char>> load_map(const std::string& archivo);

    SDL_Color get_blanco() const;

    SDL_Color get_color_translucent(const ColorTranslucent& clave) ;

    TTF_Font* get_font_menu();

    TTF_Font* get_font_game();
    TTF_Font* get_font_hud();
};

#endif  // GAMECONFIG_H
