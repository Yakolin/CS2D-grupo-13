#ifndef KNIFE_H
#define KNIFE_H
#include <memory>

#include "../../Config/GameConfig.h"
#include "../Weapon.h"
#include "FireMode/SemiAutomatic.h"

class Knife: public Weapon {

private:
    damage_t calculate_damage(float distance) override;

public:
    explicit Knife(GameConfig::weapon_config_t specs);
    ~Knife();

    bool set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) override;

    bool shoot_burst(ISpawneableZone& spawn, player_id_t id, Position& direction) override;

    bool reload() override;

    bool have_bullets() override;

    WeaponImage get_weapon_image() override;  // esto deberia salir de weapon y estar especifico
                                              // para cada caso, seria KnifeImage por ej

    bool is_droppable() override;
};

#endif  // !KNIFE_H
