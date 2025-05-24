#include "FireableWeapon.h"

void Glock::set_on_action(std::map<player_id_t, std::unique_ptr<Collider>>& damage_colliders,
                          player_id_t id, Vector2& position, Vector2& direction) {
    if (current_bullets > 0) {
        uint8_t bullets_fired = std::min(current_bullets, fire_rate);
        current_bullets -= bullets_fired;
        std::cout << "Disparaste " << bullets_fired
                  << " balas. Balas restantes: " << current_bullets << std::endl;
        damage_colliders.insert(std::make_pair(id, std::make_unique<Line>(position, direction, 2)));
    } else {
        std::cout << "No pudiste disparar balas \n";
    }
}

void FireableWeapon::reload() {
    if (max_bullets > 0 && current_bullets < magazine) {  // Si en el inventario tengo >= 0 balas
        uint8_t needed_bullets = magazine - current_bullets;
        uint8_t avalible_bullets = std::min(needed_bullets, max_bullets);
        current_bullets += avalible_bullets;
        max_bullets -= avalible_bullets;
        std::cout << "Recargas : " << avalible_bullets
                  << " balas. Balas restantes en almacenamiento: " << max_bullets << std::endl;
    } else {
        std::cout << "No tenes mas balas en el almacenamiento\no no habia porque recargar, ya "
                     "estas lleno\n";
    }
}
