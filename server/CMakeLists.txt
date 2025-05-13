target_sources(CS2D_server
    PRIVATE
    # .cpp files
    player_actions.cpp
    protocol.cpp
    
    PUBLIC
    # .h files
    game.h
    player_actions.h
    player_actions.cpp
    protocol.h
    )