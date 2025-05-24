target_sources(CS2D_server
    PRIVATE
    # .cpp files
    Colliders.cpp
    CollisionManager.cpp
    Equipement.cpp
    FireableWeapon.cpp
    GameManager.cpp
    Map.cpp
    Physics.cpp
    Player.cpp
    PlayerType.cpp

    PUBLIC
    # .h files
    CollisionManager.h
    Colliders.h
    Equipement.h
    FireableWeapon.h
    GameException.h
    GameManager.h
    Map.h
    MapTypes.h
    Physics.h
    Player.h
    PlayerType.h
    Specials.h
    Weapon.h
    )