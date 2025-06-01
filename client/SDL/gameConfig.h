#ifndef GAMECONFIG_H
#define GAMECONFIG_H
#include <fstream>
#include <string>
#include <unordered_map>
#include <iostream>
#include <yaml-cpp/yaml.h>

class GameConfig {
private:
    int window_width;
    int window_height;
    int  tile_width;
    int tile_height;

    void load(const std::string& file_path);

    void calculate_tile_size( const int& cols,const  int& rows) ;

public:
    GameConfig();

int get_window_width() const ;

int get_window_height() const ;

int get_tile_width() const ;

int get_tile_height() const ;

std::vector<std::vector<char>> load_map(const std::string& archivo) ;

};

#endif // GAMECONFIG_H
