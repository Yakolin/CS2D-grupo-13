#ifndef AWP_H
#define AWP_H

#include "../../Config/GameConfig.h"
#include "../FireableWeapon.h"
#include "FireMode/SemiAutomatic.h"

class Awp: public FireableWeapon {
private:
    damage_t calculate_damage(float distance) override;

public:
    explicit Awp(GameConfig::weapon_config_t specs);
    ~Awp();

    bool is_droppable() override;
};

#endif  // !AWP_H