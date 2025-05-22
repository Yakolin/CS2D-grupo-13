#include "Equipement.h"

void Equipement::put_bomb(std::unique_ptr<Weapon>& _bomb) {
    if (!bomb)
        return;  // Excepcion?
    bomb = std::move(_bomb);
}
