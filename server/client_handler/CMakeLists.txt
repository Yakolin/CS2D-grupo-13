target_sources(CS2D_server
    PRIVATE
    # .cpp files
    acceptor.cpp
    client_handler.cpp
    games_monitor.cpp
    game_loop.cpp

    PUBLIC
    # .h files
    acceptor.h
    client_handler.h
    games_monitor.h
    game_loop.h
    )