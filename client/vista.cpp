#include "vista.h"
#include <QApplication>
#include <QStackedWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTabWidget>

Vista::Vista(int& argc, char* argv[])
    : argc(argc), 
    argv(argv), 
    skt(argv[1],argv[2]), 
    protocolo(skt),
    opcionElegida(LobbyCommandType::NONE), 
    rutas_skins(),
    route_weapons() ,
    info_game()
    {
        
        route_weapons = {
        {Weapon::AK47, "assets/gfx/weapons/ak47.png"},
        {Weapon::AWP, "assets/gfx/weapons/awp.png"},
        {Weapon::SNIKE , "assets/gfx/weapons/knife.png"}, 
        {Weapon::AK47, "assets/gfx/weapons/m3.png"},
        {Weapon::GLOCK , "assets/gfx/weapons/glock.png"},
        {Weapon::BOMB, "assets/gfx/weapons/bomb.png"},
        };
        
        rutas_skins = {
        {Object::PHOENIX, "assets/gfx/terrorist/t2.png"},
        {Object::L337_KREW, "assets/gfx/terrorist/t4.png"},
        {Object::ARCTIC_AVENGER, "assets/gfx/terrorist/t3.png"},
        {Object::GUERRILLA, "assets/gfx/terrorist/t1_1.png"},
        {Object::SEAL, "assets/gfx/counterTerrorist/ct2.png"},
        {Object::GSG9, "assets/gfx/counterTerrorist/ct4.png"},
        {Object::SAS, "assets/gfx/counterTerrorist/ct3.png"},
        {Object::GIGN, "assets/gfx/counterTerrorist/ct1.png"}
    };

}


void Vista::run() {

    QApplication app(argc, argv);  
    MenuView menu(nullptr,protocolo);
    menu.show();

    QObject::connect(&menu, &MenuView::opcionElegida, [this,&menu](LobbyCommandType tipo, Player info){
        this->opcionElegida = tipo;
        this->info_game = info;
        menu.close();
    });
    app.exec();
    std::cout << "Nombre del jugador: " << info_game.info.name_player << std::endl;
    std::cout << "Nombre del juego: " << info_game.info.name_game << std::endl;
    std::cout << "Equipo: " << info_game.team << std::endl;
    std::cout << "Skin: " << info_game.skin << std::endl;
    std::cout << "Mapa: " << info_game.map << std::endl;
    
    if(opcionElegida != LobbyCommandType::CREATE_GAME && opcionElegida != LobbyCommandType::JOIN_GAME){
        return;
    }
    GameInfo info_game = protocolo.read_game_info();
    std::vector<Position> walls = info_game.walls;
    std::cout << "walls ===================== " << std::endl;
    std::cout << "cant walls ====== "<< walls.size() << std::endl;
    /*for (size_t i = 0; i < walls.size(); i++)
    {
        std::cout << "("<<walls[i].x<< "," << walls[i].y << ")" << std::endl;
    }*/
    
    try {
        GameView gameView(std::move(skt));
        if(!gameView.init_game() || !gameView.cargar_skins(rutas_skins) || !gameView.load_weapon(route_weapons))
            throw std::runtime_error(std::string("Error a inicializar game") );


        if(opcionElegida == LobbyCommandType::CREATE_GAME){
            if(!gameView.add_player(11,4,200.0f, rutas_skins.at(Object::GUERRILLA))){
                return;
            }
        }else{
            if(!gameView.add_player(23,9,200.0f, rutas_skins.at(Object::PHOENIX))){
                return;
            }
        }
        gameView.draw_game(walls);
    } catch (const std::exception& e) {
        std::cerr << "Excepción atrapada en vista: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Excepción desconocida en vista " << std::endl;
    }
}

Vista::~Vista() {}
