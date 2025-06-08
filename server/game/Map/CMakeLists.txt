target_sources(CS2D_server
    PRIVATE
    MapConfig.cpp
    CollisionManager.cpp
    Map.cpp

    
    PUBLIC
    MapConfig.h
    CollisionManager.h
    Map.h
    IGameZone.h
    IDroppableZone.h
    ISpawneableZone.h
    MapExeption.h
    # .h files
    )