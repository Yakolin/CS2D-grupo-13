#ifndef GAMECONFIG_H
#define GAMECONFIG_H
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <yaml-cpp/yaml.h>

class GameConfig {
private:
    int window_width;
    int window_height;
    int tile_width;
    int tile_height;
    int viewport_width;
    int viewport_height;
    std::string font;
    int size_font;
    SDL_Color blanco;

    void load(const std::string& file_path);


public:
    GameConfig();

    int get_window_width() const;

    int get_window_height() const;

    int get_tile_width() const;

    int get_tile_height() const;

    int get_viewpost_height() const;

    int get_viewpost_width() const;

    int get_size_font() const;

    std::string get_font() const;

    std::vector<std::vector<char>> load_map(const std::string& archivo);

    SDL_Color get_blanco() const;
};

#endif  // GAMECONFIG_H
