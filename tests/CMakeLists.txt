target_sources(CS2D_tests
    PRIVATE
    # .cpp files
    test_protocol_server.cpp
    test_protocol_client.cpp
    ../server/protocol.cpp
    ../server/client_action.cpp
    ../client/model/client_action.cpp
    ../client/model/protocol.cpp
    
    PUBLIC
    # .h files
    ../server/protocol.h
    ../server/game.h
    ../server/client_action.h
    ../common/player_command_types.h
    ../common/lobby_types.h
    ../client/model/client_action.h
    ../client/model/protocol.h
    )
add_subdirectory(mocks/)