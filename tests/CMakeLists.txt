target_sources(CS2D_tests
    PRIVATE
    # .cpp files
    test_protocol_server.cpp
    PUBLIC
    # .h files
    )

add_subdirectory(mocks/)