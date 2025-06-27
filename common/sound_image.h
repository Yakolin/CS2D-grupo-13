#ifndef SOUND_IMAGE_H_
#define SOUND_IMAGE_H_
#include "game_info.h"
#include "player_command_types.h"
#include "utility.h"
enum class SoundType { SHOOT, WALK, RELOAD, HIT, CHANGE_WEAPON, DROP, DIE, PICK_UP, NONE, BUY };
using distance_sound_t = std::uint16_t;

class SoundCommonImage {
public:
    SoundType type;
    distance_sound_t distance;
    SoundCommonImage(SoundType type, distance_sound_t distance): type(type), distance(distance) {}
};
class SoundShootImage: public SoundCommonImage {
public:
    WeaponCode code;
    SoundShootImage(distance_sound_t distance, WeaponCode code):
            SoundCommonImage(SoundType::SHOOT, distance), code(code) {}
};

class SoundImage {
public:
    std::vector<SoundCommonImage> common_sounds;
    std::vector<SoundShootImage> shoot_sounds;
    SoundImage() = default;
    SoundImage(std::vector<SoundCommonImage>&& sounds, std::vector<SoundShootImage>&& shoot_sounds):
            common_sounds(std::move(sounds)), shoot_sounds(std::move(shoot_sounds)) {}
};
#endif  // SOUND_IMAGE_H_
