target_sources(CS2D_common
    PRIVATE
    # .cpp files
    constant_rate_loop.cpp
    liberror.cpp
    resolver.cpp
    resolvererror.cpp
    socket.cpp

    PUBLIC
    # .h files
    client_common_action.h
    constant_rate_loop.h
    game_image.h
    liberror.h
    lobby_types.h
    player_types.h
    queue.h
    resolver.h
    resolvererror.h
    socket.h
    thread.h
    utility.h
    )