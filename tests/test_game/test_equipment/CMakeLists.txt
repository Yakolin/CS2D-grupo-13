target_sources(CS2D_tests
    PRIVATE
    ../../../server/game/Equipment.cpp
    
    PUBLIC
    ../../../common/player_command_types.h
    ../../../server/game/Equipment.h
    ../../mocks/mock_droppable_zone.h
    ../../../server/game/IDropeableZone.h
    ../../../server/game/FireableWeapon.h
    ../../../server/game/IDropeableZone.h
    ../../../server/game/ISpawneableZone.h
    ../../../server/game/SpecialWeapons.h

)