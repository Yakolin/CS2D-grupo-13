#ifndef SOUND_MANAGER_H_
#define SOUND_MANAGER_H_
#include <memory>
#include <vector>

#include "Sound.h"
class SoundManager {
    std::vector<Sound> sounds;

public:
    SoundManager() = default;
    void emit_sound(Sound sound) { sounds.push_back(sound); }
    std::vector<Sound> get_emited_sounds() {
        std::vector<Sound> aux = this->sounds;
        this->sounds.clear();
        return aux;
    };
};
#endif  // SOUND_MANAGER_H_