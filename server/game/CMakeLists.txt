target_sources(CS2D_server
    PRIVATE
    # .cpp files
    Colliders.cpp
    CollisionManager.cpp
    Equipment.cpp
    FireableWeapon.cpp
    GameManager.cpp
    Map.cpp
    Player.cpp
    SpecialWeapons.cpp
    
    PUBLIC
    # .h files
    CollisionManager.h
    Colliders.h
    Equipment.h
    FireableWeapon.h
    GameException.h
    GameManager.h
    ICanInteract.h
    IGameZone.h
    Map.h
    Player.h
    SpecialWeapons.h
    Weapon.h
    Timer.h
    )