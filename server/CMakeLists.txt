target_sources(CS2D_server
    PRIVATE
    # .cpp files
    main.cpp
    server.cpp
    acceptor.cpp
    
    PUBLIC
    # .h files
    server.h
    acceptor.h
    )
add_subdirectory(interfaces/)
add_subdirectory(protocol/)
