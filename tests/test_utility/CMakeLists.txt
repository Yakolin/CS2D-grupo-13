target_sources(CS2D_tests
    PRIVATE
    test_queue.cpp

    PUBLIC
    ../../common/player_command_types.h
    ../../common/queue.h
    ../../server/protocol/client_action.h
)