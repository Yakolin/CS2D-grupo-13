target_sources(CS2D_server
    PRIVATE
    FireableWeapon.cpp
    SpecialWeapons.cpp
    WeaponFactory.cpp
    PUBLIC
    FireableWeapon.h
    SpecialWeapons.h
    WeaponFactory.h
    Weapon.h
    IInteractuable.h
    # .h files
    )
    add_subdirectory(guns/)