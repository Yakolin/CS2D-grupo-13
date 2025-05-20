target_sources(CS2D_server
    PRIVATE
    # .cpp files
    main.cpp
    server.cpp
    acceptor.cpp
    protocol.cpp
    game.cpp

    PUBLIC
    # .h files
    server.h
    acceptor.h
    protocol.h
    game.h
    )
add_subdirectory(protocol/)
add_subdirectory(handlers/)