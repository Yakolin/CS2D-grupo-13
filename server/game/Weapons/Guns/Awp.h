#ifndef AWP_H
#define AWP_H

#include "../../Config/GameConfig.h"
#include "../FireableWeapon.h"
#include "FireMode/SemiAutomatic.h"

class Awp: public FireableWeapon {
private:
    uint8_t calculate_damage(float distance);

public:
    explicit Awp(GameConfig::weapon_config_t specs);
    ~Awp();
    virtual bool set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override;


    virtual bool is_droppable() override;
};

#endif  // !AWP_H