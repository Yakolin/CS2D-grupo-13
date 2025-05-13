target_sources(CS2D_server
    PRIVATE
    # .cpp files
    main.cpp
    protocol.cpp
    player_action.cpp

    PUBLIC
    # .h files
    game.h
    player_action.h
    protocol.h
    )