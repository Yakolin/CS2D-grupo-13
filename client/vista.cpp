#include "vista.h"

#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QTabWidget>
#include <QVBoxLayout>

Vista::Vista(int& argc, char* argv[]):
        argc(argc),
        argv(argv),
        skt(argv[1], argv[2]),
        protocolo(skt),
        opcionElegida(LobbyCommandType::NONE),
        info_game() {}

void imprimir_game_info(const GameInfo& game_info) {
    
    auto to_string_map = [](MapName map) -> const char* {
        switch (map) {
            case MapName::DESIERTO: return "Desierto";
            case MapName::PUEBLITO_AZTECA: return "Pueblito Azteca";
            case MapName::ZONA_ENTRENAMIENTO: return "Zona de Entrenamiento";
            default: return "Desconocido";
        }
    };

    auto to_string_weapon = [](WeaponCode code) -> const char* {
        switch (code) {
            case WeaponCode::KNIFE: return "Cuchillo";
            case WeaponCode::GLOCK: return "Pistola";
            case WeaponCode::AWP : return "Rifle";
            case WeaponCode::AK47 : return "Francotirador";
            default: return "Desconocida";
        }
    };

    auto to_string_pos = [](const Position& p) -> std::string {
        return "(" + std::to_string(p.x) + ", " + std::to_string(p.y) + ")";
    };

    const MapInfo& mapa = game_info.map_info;

    std::cout << "==== INFORMACIÓN DEL JUEGO ====" << std::endl;
    std::cout << "Mapa: " << to_string_map(mapa.map_name) << std::endl;

    std::cout << "Zona Bomba A: " << to_string_pos(mapa.bomb_A.pos_min)
              << " hasta " << to_string_pos(mapa.bomb_A.pos_max) << std::endl;

    std::cout << "Zona Bomba B: " << to_string_pos(mapa.bomb_B.pos_min)
              << " hasta " << to_string_pos(mapa.bomb_B.pos_max) << std::endl;

    std::cout << "Spawn Terrorista: " << to_string_pos(mapa.spawn_TT.pos_min)
              << " hasta " << to_string_pos(mapa.spawn_TT.pos_max) << std::endl;

    std::cout << "Spawn Antiterrorista: " << to_string_pos(mapa.spawn_CT.pos_min)
              << " hasta " << to_string_pos(mapa.spawn_CT.pos_max) << std::endl;

    std::cout << "Paredes (" << mapa.walls.size() << "):" << std::endl;
    for (const auto& pos : mapa.walls)
        std::cout << " - " << to_string_pos(pos) << std::endl;

    std::cout << "Armas comprables (" << game_info.weapons_purchasables.size() << "):" << std::endl;
    for (const auto& arma : game_info.weapons_purchasables)
        std::cout << " - " << to_string_weapon(arma.code) << ": $" << arma.price << std::endl;

    std::cout << "================================" << std::endl;
}

void dibujar_mapa(const MapInfo& mapa, int ancho, int alto) {
    std::vector<std::string> grid(alto, std::string(ancho, '.'));

    for (const auto& wall : mapa.walls) {
        grid[wall.y][wall.x] = '#';
    }

    for (const auto& box : mapa.boxes) {
        grid[box.y][box.x] = 'B';
    }

    for (int y = mapa.bomb_A.pos_min.y; y <= mapa.bomb_A.pos_max.y; ++y) {
        for (int x = mapa.bomb_A.pos_min.x; x <= mapa.bomb_A.pos_max.x; ++x) {
            grid[y][x] = 'A';
        }
    }

    for (int y = mapa.bomb_B.pos_min.y; y <= mapa.bomb_B.pos_max.y; ++y) {
        for (int x = mapa.bomb_B.pos_min.x; x <= mapa.bomb_B.pos_max.x; ++x) {
            grid[y][x] = 'a';
        }
    }

    for (int y = mapa.spawn_TT.pos_min.y; y <= mapa.spawn_TT.pos_max.y; ++y) {
        for (int x = mapa.spawn_TT.pos_min.x; x <= mapa.spawn_TT.pos_max.x; ++x) {
            grid[y][x] = 'T';
        }
    }

    for (int y = mapa.spawn_CT.pos_min.y; y <= mapa.spawn_CT.pos_max.y; ++y) {
        for (int x = mapa.spawn_CT.pos_min.x; x <= mapa.spawn_CT.pos_max.x; ++x) {
            grid[y][x] = 'C';
        }
    }

    // Imprimir
    for (const auto& fila : grid) {
        std::cout << fila << '\n';
    }
}


bool Vista::showLobby(){
    QApplication app(argc, argv);
    MenuView menu(nullptr, protocolo);
    menu.show();

    QObject::connect(&menu, &MenuView::opcionElegida,
                     [this, &menu](LobbyCommandType tipo, Player info) {
                         this->opcionElegida = tipo;
                         this->info_game = info;
                         menu.close();
                     });
    app.exec();

    if (opcionElegida != LobbyCommandType::CREATE_GAME &&
        opcionElegida != LobbyCommandType::JOIN_GAME) {
        return false;
    }
    return true;
}



bool Vista::init_game( SDL_Window*& ventana, SDL_Renderer*& renderer, const GameConfig& config) {
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(std::string("Error al inicializar SDL: ") + SDL_GetError());
        return false;
    }

    ventana = SDL_CreateWindow(
            "Mapa", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, config.get_window_width(),
            config.get_window_height(), SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!ventana) {
        throw std::runtime_error(std::string("Error al crear la ventana: ") + SDL_GetError());
    }
    renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        throw std::runtime_error(std::string("Error al crear el renderer: ") + SDL_GetError());
    }
    SDL_RenderSetLogicalSize(renderer, config.get_viewpost_width(), config.get_viewpost_height());
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("No se pudo inicializar SDL_mixer: %s\n", Mix_GetError());
        return 1;
    }
    SDL_ShowCursor(SDL_DISABLE);
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);

    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG))) {
        throw std::runtime_error(std::string("Error inicializando SDL_image: ") + IMG_GetError());
        return false;
    }
    return true;
}


void Vista::free_components( SDL_Window* ventana, SDL_Renderer* renderer){
    if (renderer)
        SDL_DestroyRenderer(renderer);

    if (ventana)
        SDL_DestroyWindow(ventana);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Vista::showGame(){

    GameInfo info_game_view = protocolo.read_game_info();
    std::cout << "Mapa bx: " << info_game_view.map_info.boxes.size() << std::endl;

    //dibujar_mapa(info_game_view.map_info,40,40);
    Acknowledge ack = Acknowledge::READY;
    protocolo.send_acknowledge(ack); 
    SDL_Window* ventana = nullptr;
    SDL_Renderer* renderer = nullptr;
    GameConfig config;
    if( !init_game(ventana,renderer,config))
        throw std::runtime_error(std::string("Error a inicializar game"));

    ManageTexture manger_texture(renderer);
    SDL_Texture* textura = manger_texture.get(Object::FONDO_ESPERA);
    SDL_RenderCopy(renderer, textura, nullptr, nullptr);
    SDL_RenderPresent(renderer);

    try {   
        GameView gameView(std::move(skt), info_game_view, info_game, ventana, renderer,manger_texture,config);
        gameView.start(info_game_view);
        gameView.run();
    } catch (const QuitGameException& e) {  
        free_components(ventana,renderer);       
    } catch (const std::exception& e) {
        std::cerr << "Excepción atrapada en vista: " << e.what() << std::endl;
        free_components(ventana,renderer);
    } catch (...) {
        std::cerr << "Excepción desconocida en vista " << std::endl;
        free_components(ventana,renderer);
    }
}

void Vista::showScoreboard(){

    QApplication app(argc, argv);
    ScoreBoard score;
    score.show_scores_game();
    app.exec();

}


Vista::~Vista() {
    
}
