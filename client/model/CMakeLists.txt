target_sources(CS2D_client
    PRIVATE
    # .cpp files
    protocol.cpp
    receiver.cpp
    sender.cpp
    client_action.cpp

    PUBLIC
    # .h files
    protocol.h
    receiver.h
    sender.h
    client_action.h
    )
