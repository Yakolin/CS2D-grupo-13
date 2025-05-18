target_sources(CS2D_client
    PRIVATE

    client.cpp
    clientMain.cpp
    controller.cpp
    clientMain.cpp
    lobbyView.cpp
    gameView.cpp
    mapView.cpp
    playerView.cpp
    scoreboard.cpp

    PUBLIC
    gameView.cpp
    gameView.h
    lobbyView.h
    mapView.h
    playerView.h
    scoreboard.h
    client.h
    controller.h
    lobbyView.h
    )

add_subdirectory(model/)
