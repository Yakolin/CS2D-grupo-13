target_sources(CS2D_server
    PRIVATE
    # .cpp files
    main.cpp
    player_actions.cpp
    protocol.cpp


    PUBLIC
    # .h files
    game.h
    player_actions.h
    player_actions.cpp
    protocol.h
    )