#ifndef GLOCK_H
#define GLOCK_H

#include <memory>

#include "../../Config/GameConfig.h"
#include "../FireableWeapon.h"
#include "FireMode/SemiAutomatic.h"
class Glock: public FireableWeapon {
private:
    damage_t calculate_damage(float distance) override;

public:
    explicit Glock(GameConfig::weapon_config_t specs);
    ~Glock();

    bool is_droppable() override;
};


#endif  // !GLOCK_H
