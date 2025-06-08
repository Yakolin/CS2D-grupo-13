target_sources(CS2D_tests
    PRIVATE
    ../../../server/game/Player/Equipment.cpp
    test_equipment.cpp
    
    PUBLIC
    ../../../common/player_command_types.h
    ../../../server/game/Player/Equipment.h
    ../../mocks/mock_droppable_zone.h
    ../../../server/game/Map/IDroppableZone.h
    ../../../server/game/Weapons/FireableWeapon.h
    ../../../server/game/Map/IDroppableZone.h
    ../../../server/game/Map/ISpawneableZone.h
    ../../../server/game/Weapons/SpecialWeapons.h

)