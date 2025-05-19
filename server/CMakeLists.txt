target_sources(CS2D_server
    PRIVATE
    # .cpp files
    main.cpp
    game.cpp
    server.cpp

    PUBLIC
    # .h files
    game.h
    server.h
    )
add_subdirectory(server/)
add_subdirectory(protocol/)