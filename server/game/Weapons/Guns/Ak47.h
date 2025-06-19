#ifndef AK_H
#define AK_H

#include "../../Config/GameConfig.h"
#include "../FireableWeapon.h"
#include "FireMode/Automatic.h"

class Ak47: public FireableWeapon {

private:
    damage_t calculate_damage() override;

public:
    explicit Ak47(GameConfig::weapon_config_t specs);
    ~Ak47();

    bool is_droppable() override;
};

#endif  // !AK_H