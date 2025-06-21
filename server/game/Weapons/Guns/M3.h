#ifndef M3_H
#define M3_H

#include "../../Config/GameConfig.h"
#include "../FireableWeapon.h"
#include "FireMode/SemiAutomatic.h"

class M3: public FireableWeapon {
private:
    damage_t calculate_damage(float distance) override;

public:
    explicit M3(GameConfig::weapon_config_t specs);
    ~M3();

    bool is_droppable() override;
};

#endif  // !M3_H