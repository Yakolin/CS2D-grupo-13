target_sources(CS2D_server
    PRIVATE
    # .cpp files
    main.cpp
    server.cpp
    acceptor.cpp
    game.cpp
    
    PUBLIC
    # .h files
    server.h
    acceptor.h
    game.h
    )
add_subdirectory(interfaces/)
add_subdirectory(protocol/)
    
