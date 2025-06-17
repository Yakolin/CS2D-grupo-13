#ifndef GLOCK_H
#define GLOCK_H

#include "../FireableWeapon.h"

class Glock: public FireableWeapon {
private:
    uint8_t calculate_damage(float distance);

public:
    explicit Glock(GameConfig::weapon_config_t specs);
    ~Glock();

    virtual bool set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override;
    virtual bool is_droppable() override;
};


#endif  // !GLOCK_H
