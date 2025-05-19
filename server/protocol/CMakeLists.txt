target_sources(CS2D_server
    PRIVATE
    # .cpp files
    client_action.cpp
    functor_parse_client_action.cpp
    protocol.cpp
    receiver.cpp
    sender.cpp

    PUBLIC
    # .h files
    client_action.h
    functor_parse_client_action.h
    protocol.h
    receiver.h
    sender.h
    )