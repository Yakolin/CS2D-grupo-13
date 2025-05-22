target_sources(CS2D_client
    PRIVATE
    # .cpp files
    ../../common/socket.cpp
    protocol.cpp
    receiver.cpp
    sender.cpp
    client_action.cpp

    PUBLIC
    # .h files
    ../../common/queue.h
    ../../common/socket.h
    protocol.h
    receiver.h
    sender.h
    client_action.h
    ../../common/connection_closed_exception.h
    ../../common/game_image.h
    ../../common/lobby_types.h
    ../../common/player_types.h
    ../../common/thread.h
    ../../common/client_common_action.h
    )
