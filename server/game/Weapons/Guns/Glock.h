#ifndef GLOCK_H
#define GLOCK_H

#include "../../Config/GameConfig.h"
#include "../FireableWeapon.h"
#include "FireMode/SemiAutomatic.h"

class Glock: public FireableWeapon {
private:
    damage_t calculate_damage() override;

public:
    explicit Glock(GameConfig::weapon_config_t specs);
    ~Glock();

    bool is_droppable() override;
};


#endif  // !GLOCK_H
