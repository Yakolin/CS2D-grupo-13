target_sources(CS2D_server

    PRIVATE
    # .cpp files
    GameManager.cpp
    PUBLIC
    # .h files
    GameException.h
    GameManager.h
    Timer.h
    TimerActions.h
    )
add_subdirectory(Colliders/)
add_subdirectory(Player/)
add_subdirectory(Config/)
add_subdirectory(Map/)
add_subdirectory(Weapons/)