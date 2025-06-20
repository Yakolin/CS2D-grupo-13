#ifndef SOUND_MANAGER_H_
#define SOUND_MANAGER_H_
#include <memory>
#include <vector>

#include "../../../common/utility.h"

#include "Sound.h"
class SoundManager {
    std::vector<std::pair<Sound, Position>> sounds;

public:
    SoundManager() = default;
    void emit_sound(const Sound& sound, const Position& pos) {
        sounds.push_back(std::make_pair(sound, pos));
    }
    std::vector<std::pair<Sound, Position>> get_emited_sounds() {
        std::vector<std::pair<Sound, Position>> aux = this->sounds;
        this->sounds.clear();
        return aux;
    };
};
#endif  // SOUND_MANAGER_H_