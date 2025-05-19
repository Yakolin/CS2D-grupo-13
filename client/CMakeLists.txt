target_sources(CS2D_client
    PRIVATE

    client.cpp
    controller.cpp
    main.cpp
    lobbyView.cpp
    gameView.cpp
    mapView.cpp
    playerView.cpp
    scoreboard.cpp
    manageTexture.cpp
    menuView.cpp
    PUBLIC
    
    gameView.h
    lobbyView.h
    mapView.h
    playerView.h
    scoreboard.h
    client.h
    controller.h
    lobbyView.h
    manageTexture.h
    menuView.h
    renderizable.h
    tipos.h

    )

add_subdirectory(model/)
