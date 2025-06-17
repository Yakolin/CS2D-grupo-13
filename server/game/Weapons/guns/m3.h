#ifndef M3_H
#define M3_H

#include "../../Config/GameConfig.h"
#include "../FireableWeapon.h"

class M3: public FireableWeapon {
private:
    uint8_t calculate_damage(float distance);

public:
    explicit M3(GameConfig::weapon_config_t specs);
    ~M3();
    virtual bool set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override;
    virtual bool is_droppable() override;
};

#endif  // !M3_H