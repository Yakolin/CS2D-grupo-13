#include "vista.h"

#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <iomanip>

Vista::Vista(int& argc, char* argv[]):
        argc(argc),
        argv(argv),
        skt(argv[1], argv[2]),
        protocolo(skt),
        opcionElegida(LobbyCommandType::NONE),
        info_game() {}




bool Vista::showLobby() {
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


bool Vista::init_game(SDL_Window*& ventana, SDL_Renderer*& renderer, const GameConfig& config) {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(std::string("Error al inicializar SDL: ") + SDL_GetError());
        return false;
    }

    ventana = SDL_CreateWindow("Mapa", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               config.get_window_width(), config.get_window_height(),
                               SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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


void Vista::free_components(SDL_Window* ventana, SDL_Renderer* renderer) {
    if (renderer)
        SDL_DestroyRenderer(renderer);

    if (ventana)
        SDL_DestroyWindow(ventana);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

std::map<player_id_t, InfoPlayer> Vista::showGame() {

    GameInfo info_game_view = protocolo.read_game_info();
    std::cout << "Mapa bx: " << info_game_view.map_info.boxes.size() << std::endl;
    Acknowledge ack = Acknowledge::READY;
    protocolo.send_acknowledge(ack);
    SDL_Window* ventana = nullptr;
    SDL_Renderer* renderer = nullptr;
    GameConfig config;
    if (!init_game(ventana, renderer, config))
        throw std::runtime_error(std::string("Error a inicializar game"));

    ManageTexture manger_texture(renderer);
    SDL_Texture* textura = manger_texture.get(Object::FONDO_ESPERA);
    SDL_RenderCopy(renderer, textura, nullptr, nullptr);
    SDL_RenderPresent(renderer);
    std::map<player_id_t, InfoPlayer> table;
    GameView gameView(skt, info_game_view, info_game, ventana, renderer, manger_texture, config);
    try {
        gameView.run();
    } catch (const QuitGameException& e) {
        table = gameView.get_info_players_map();
        free_components(ventana, renderer);
    } catch (const std::exception& e) {
        std::cerr << "Excepción atrapada en vista: " << e.what() << std::endl;
        free_components(ventana, renderer);
    } catch (...) {
        std::cerr << "Excepción desconocida en vista " << std::endl;
        free_components(ventana, renderer);
    }
    return table;
}

void Vista::showScoreboard(const std::map<player_id_t, InfoPlayer>& table) {
    QApplication app(argc, argv);
    ScoreBoard score(table);

    QMessageBox msgBox;
    msgBox.setWindowTitle("Pregunta");
    msgBox.setText("¿ Quieres ve la tabla de estadisticas ?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes) {
        score.show_scores_game();
        app.exec();
    }
}

void Vista::reset() {
    this->opcionElegida = LobbyCommandType::NONE;
    this->info_game.info.name_game = "";
    this->info_game.info.name_player = "";
    this->info_game.map = "";
    this->info_game.skin2 = "";
    this->info_game.skin = "";
    this->info_game.team = "";
}

Vista::~Vista() {
    this->skt.shutdown(2);
    this->skt.close();
}
