#ifndef I_DROPPABLE_ZONE_H_
#define I_DROPPABLE_ZONE_H_
#include <memory>

#include "../../../common/utility.h"
#include "../Weapons/Weapon.h"
class IDroppableZone {
public:
    virtual void drop(const player_id_t& player_id, std::shared_ptr<IInteractuable>& dropeable) = 0;
    virtual bool plant_bomb(const player_id_t& player_id) = 0;
    virtual ~IDroppableZone() = default;
};
#endif  //  I_DROPPABLE_ZONE_H_
