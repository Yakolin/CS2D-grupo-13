#include "FireableWeapon.h"

#include "Map.h"
// Duda a como resolver esto, que pasa si quiero de igual forma que exista este metodo de superclase
// que sea fire pero que sea generico?
//  quiza no se, la glock y la usp y las demas disparan de igual forma (en este ejemplo del tp quiza
//  no) pero quiero que puedan usar ese metodo implementado por el padre?

void Glock::fire(Map& map, player_id_t id, Vector2& position, Vector2& direction) {
    if (current_bullets > 0) {
        int bullets_fired = std::min(current_bullets, fire_rate);
        current_bullets -= bullets_fired;
        // Instanciar balas por tiempo y demas
        // Por ahora laburo con solo una bala
        Bullet::BulletSpeeds velocidades;
        Bullet bullet(id, position, direction, velocidades.mid_bullet, 5);
        map.add_bullet(bullet);
    } else {
        std::cout << "No pudiste disparar balas \n";
    }
}

void FireableWeapon::reload() {
    if (max_bullets > 0 && current_bullets < magazine) {  // Si en el inventario tengo >= 0 balas
        int needed_bullets = magazine - current_bullets;
        int avalible_bullets = std::min(needed_bullets, max_bullets);
        current_bullets += avalible_bullets;
        max_bullets -= avalible_bullets;
        std::cout << "Recargas : " << avalible_bullets
                  << " balas. Balas restantes en almacenamiento: " << max_bullets << std::endl;
    } else {
        std::cout << "No tenes mas balas en el almacenamiento\no no habia porque recargar, ya "
                     "estas lleno\n";
    }
}
