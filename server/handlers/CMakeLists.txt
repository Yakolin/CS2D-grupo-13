target_sources(CS2D_server
    PRIVATE
    # .cpp files
    lobby_handler.cpp
    player_handler.cpp
    games_monitor.cpp
    game_loop.cpp

    PUBLIC
    # .h files
    lobby_handler.h
    player_handler.h
    games_monitor.h
    game_loop.h
    )