#ifndef KNIFE_H
#define KNIFE_H

#include "../../Config/GameConfig.h"
#include "../Weapon.h"

class Knife: public Weapon {
public:
    explicit Knife(GameConfig::weapon_config_t specs);
    ~Knife();

    virtual bool set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override;
    virtual void reload() override;
    virtual void restore_bullets() override {}  // Quiza aca no deberia ir esto... desp lo veo bien
    virtual WeaponImage get_weapon_image() override;
    virtual bool is_droppable() override;
};

#endif  // !KNIFE_H
