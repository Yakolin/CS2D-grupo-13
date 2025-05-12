target_sources(CS2D_server
    PRIVATE
    # .cpp files
    main.cpp
    server.cpp
    acceptor.cpp
    client_handler.cpp
    games_monitor.cpp
    game_loop.cpp
    player.cpp
    receiver.cpp
    sender.cpp
    protocol.cpp

    PUBLIC
    # .h files
    main.h
    server.h
    acceptor.h
    client_handler.h
    games_monitor.h
    game_loop.h
    player.h
    receiver.h
    sender.h
    protocol.h

    )