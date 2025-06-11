target_sources(CS2D_client
    PRIVATE

    client.cpp
    controller.cpp
    main.cpp
    Qt/lobbyView.cpp
    SDL/gameView.cpp
    SDL/gameConfig.cpp
    SDL/mapView.cpp
    SDL/bomb.cpp
    SDL/fieldOfView.cpp
    SDL/playerView.cpp
    SDL/HUD.cpp
    SDL/shopping.cpp
    SDL/weaponView.cpp
    SDL/camera.cpp
    SDL/text.cpp
    Qt/scoreBoard.cpp
    SDL/manageTexture.cpp
    Qt/menuView.cpp
    vista.cpp
    PUBLIC
    
    SDL/gameView.h
    SDL/mapView.h
    SDL/playerView.h
    SDL/gameConfig.h
    SDL/HUD.h
    SDL/fieldOfView.h
    SDL/bomb.h
    SDL/shopping.h
    SDL/weaponView.h
    SDL/camera.h
    SDL/text.h
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
