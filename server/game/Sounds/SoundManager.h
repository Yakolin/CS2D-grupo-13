#ifndef SOUND_MANAGER_H_
#define SOUND_MANAGER_H_
#include <memory>
#include <utility>
#include <vector>

#include "../../../common/utility.h"

#include "Sound.h"
#include "SoundShoot.h"
class SoundManager {
private:
    std::vector<std::pair<std::shared_ptr<Sound>, Position>> sounds;

    std::vector<SoundCommonImage> common_sounds;
    std::vector<SoundShootImage> shoot_sounds;
    void handle_type(std::pair<std::shared_ptr<Sound>, Position>& sound_pair,
                     distance_sound_t distance);

public:
    SoundManager() = default;
    void emit_sound(std::shared_ptr<Sound> sound, const Position& pos) {
        sounds.push_back(std::make_pair(std::move(sound), pos));
    }
    SoundImage get_sound_image(const Position& player_pos);
    void reset() { sounds.clear(); }
};
#endif  // SOUND_MANAGER_H_
