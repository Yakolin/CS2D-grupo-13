#ifndef SOUND_MANAGER_H_
#define SOUND_MANAGER_H_
#include <memory>
#include <vector>

#include "../../../common/utility.h"

#include "Sound.h"
class SoundManager {
    std::vector<std::pair<std::shared_ptr<Sound>, Position>> sounds;

public:
    SoundManager() = default;
    void emit_sound(std::shared_ptr<Sound>& sound, const Position& pos) {
        sounds.push_back(std::make_pair(std::move(sound), pos));
    }
    std::vector<std::pair<std::shared_ptr<Sound>, Position>> get_emited_sounds() {
        std::vector<std::pair<std::shared_ptr<Sound>, Position>> aux = this->sounds;
        this->sounds.clear();
        return aux;
    };
};
#endif  // SOUND_MANAGER_H_