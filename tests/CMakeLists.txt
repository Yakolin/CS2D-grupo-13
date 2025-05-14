target_sources(CS2D_tests
    PRIVATE
    # .cpp files
    test_protocol_server.cpp
    ../server/protocol.cpp
    ../server/player_action.cpp
    
    PUBLIC
    # .h files
    ../server/protocol.h
    ../server/game.h
    ../server/player_action.h
    )
add_subdirectory(mocks/)