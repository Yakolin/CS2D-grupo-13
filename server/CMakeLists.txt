target_sources(CS2D_server
    PRIVATE
    # .cpp files
    main.cpp
    protocol.cpp
    client_action.cpp

    PUBLIC
    # .h files
    game.h
    client_action.h
    protocol.h
    games_monitor.h
    )