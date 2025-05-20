target_sources(CS2D_server
    PRIVATE
    # .cpp files
    protocol.cpp
    client_action.cpp
    functor_parse_client_action.cpp
    receiver.cpp
    sender.cpp

    PUBLIC
    # .h files
    protocol.h
    client_action.h
    functor_parse_client_action.h
    receiver.h
    sender.h
    )