target_sources(CS2D_common
    PRIVATE
    # .cpp files
    liberror.cpp
    resolver.cpp
    resolvererror.cpp
    socket.cpp

    
    PUBLIC
    # .h files
    liberror.h
    player_command_types.h
    queue.h

    resolver.h
    resolvererror.h
    socket.h
    thread.h

    connection_closed_exception.h
    client_common_action.h

    )