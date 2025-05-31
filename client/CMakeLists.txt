target_sources(CS2D_client
    PRIVATE

    client.cpp
    controller.cpp
    main.cpp
    Qt/lobbyView.cpp
    SDL/gameView.cpp
    SDL/mapView.cpp
    SDL/playerView.cpp
    Qt/scoreBoard.cpp
    SDL/manageTexture.cpp
    Qt/menuView.cpp
    vista.cpp
    PUBLIC
    
    SDL/gameView.h
    SDL/mapView.h
    SDL/playerView.h
    Qt/scoreBoard.h
    client.h
    controller.h
    Qt/lobbyView.h
    SDL/manageTexture.h
    Qt/menuView.h
    SDL/renderizable.h
    tipos.h
    vista.h

    )

add_subdirectory(model/)
