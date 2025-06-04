target_sources(CS2D_server
    PRIVATE
    # .cpp files
    protocol.cpp
    client_action.cpp
    functor_parse_client_action.cpp
    game_loop.cpp
    games_monitor.cpp
    receiver.cpp
    sender.cpp
    client_handler.cpp
    ../../common/liberror.cpp

    PUBLIC
    # .h files
    protocol.h
    client_action.h
    functor_parse_client_action.h
    game_loop.h
    games_monitor.h
    receiver.h
    sender.h
    client_handler.h
    ../../common/liberror.h
    )