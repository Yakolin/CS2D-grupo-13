#ifndef I_SOUND_ZONE_H_
#define I_SOUND_ZONE_H_
#include <utility>

#include "../../../common/game_image.h"
#include "../../../common/utility.h"

class ISoundZone {
public:
    virtual void want_emit_sound(const player_id_t& id, SoundType sound) = 0;
    virtual ~ISoundZone() = default;
};

#endif  // I_SOUND_ZONE_H_