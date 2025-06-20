#ifndef SOUND_MANAGER_H_
#define SOUND_MANAGER_H_
#include <map>
#include <memory>

#include "Sound.h"
class SoundManager {
    std::map<Sound, Position> sounds;

public:
    SoundManager() = default;
    void emit_sound(const Sound& sound, const Position& pos) {
        sounds.insert(std::make_pair(sound, pos));
    }
    std::map<Sound, Position> get_emited_sounds() {
        std::map<Sound, Position> aux = this->sounds;
        this->sounds.clear();
        return aux;
    };
};
#endif  // SOUND_MANAGER_H_