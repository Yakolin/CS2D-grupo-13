#ifndef I_DROPPABLE_ZONE_H_
#define I_DROPPABLE_ZONE_H_
#include <memory>

#include "../../common/utility.h"

#include "Weapon.h"
class IDroppableZone {
public:
    virtual void drop(std::unique_ptr<Weapon> dropeable, Position& direction) = 0;
    ~IDroppableZone() = default;
};
#endif  //  I_DROPPABLE_ZONE_H_
