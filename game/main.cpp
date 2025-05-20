#include <iostream>
#include <cassert>
#include <cmath>
#include "GameManager.h"


void print_player_images(const GameImage& image){
    for (PlayerImage player : image.players_images){
        std::cout << "| ID : " << player.player_id << 
        " | Position : (" << player.position.x << "," << player.position.y <<
        ") | Health : " << player.health << " | Points : " << player.points << std::endl;  
    }
}

bool float_eq(float a, float b, float eps = 1e-5) {
    return std::fabs(a - b) < eps;
}

void TestsVector2(){
}
int main() {
    GameManager game("Partida de prueba", "mapa1");
    game.add_player("Jugador1", 0);
    game.add_player("Jugador2", 1);
    game.start_game();
    GameImage frame = game.get_frame();
    print_player_images(frame);
    TestsVector2();
    game.shoot(1,24,25);
    frame = game.get_frame();
    print_player_images(frame);
        frame = game.get_frame();
    print_player_images(frame);
        frame = game.get_frame();
    print_player_images(frame);
        frame = game.get_frame();
    print_player_images(frame);
        frame = game.get_frame();
    print_player_images(frame);
    game.plant_bomb(0);
    game.plant_bomb(1);
    game.move(1, MoveType::RIGHT);
    game.move(1, MoveType::UP);
    game.move(1, MoveType::RIGHT);
    game.move(1, MoveType::UP);
    game.plant_bomb(0);
    game.plant_bomb(1);
    frame = game.get_frame();
    print_player_images(frame);
    return 0;
}