target_sources(CS2D_server
    PRIVATE
    CollisionManager.cpp
    Map.cpp
    
    PUBLIC
    CollisionManager.h
    Map.h
    IGameZone.h
    IDroppableZone.h
    ISpawneableZone.h
    MapExeption.h
    # .h files
    )