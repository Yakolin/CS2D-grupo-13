target_sources(CS2D_tests
    PRIVATE
    # .cpp files
    test_protocol_server.cpp
    test_protocol_client.cpp
    ../server/protocol/protocol.cpp
    ../server/protocol/client_action.cpp
    ../client/model/client_action.cpp
    ../client/model/protocol.cpp

    PUBLIC
    # .h files
    ../server/protocol/protocol.h
    ../server/protocol/client_action.h
    ../server/game.h
    ../common/player_command_types.h
    ../common/client_common_action.h
    ../server/interfaces/interface_player_action.h
    ../server/interfaces/interface_game.h
    )
add_subdirectory(mocks/)
