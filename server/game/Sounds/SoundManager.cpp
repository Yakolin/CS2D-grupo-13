#include "SoundManager.h"

#include <iostream>
void SoundManager::handle_type(std::pair<std::shared_ptr<Sound>, Position>& sound_pair,
                               distance_sound_t distance) {
    switch (sound_pair.first->sound) {
        case SoundType::SHOOT: {
            std::shared_ptr<SoundShoot> sound =
                    std::static_pointer_cast<SoundShoot>(sound_pair.first);
            shoot_sounds.push_back(SoundShootImage(distance, sound->code));
            break;
        }
        default: {
            common_sounds.push_back(SoundCommonImage(sound_pair.first->sound, distance));
            break;
        }
    }
}
SoundImage SoundManager::get_sound_image(const Position& player_pos) {
    for (auto& it: sounds) {
        int dx = player_pos.x - it.second.x;
        int dy = player_pos.y - it.second.y;
        float aux_distance = std::sqrt(dx * dx + dy * dy);
        distance_sound_t distance = static_cast<distance_sound_t>(aux_distance);
        switch (it.first->sound) {
            case SoundType::SHOOT: {
                std::shared_ptr<SoundShoot> sound = std::static_pointer_cast<SoundShoot>(it.first);
                shoot_sounds.push_back(SoundShootImage(distance, sound->code));
                break;
            }
            default: {
                common_sounds.push_back(SoundCommonImage(it.first->sound, distance));
                break;
            }
        }
    }
    return SoundImage(std::move(common_sounds), std::move(shoot_sounds));
}
