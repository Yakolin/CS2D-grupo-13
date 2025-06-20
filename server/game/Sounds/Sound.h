#ifndef SOUND_H_
#define SOUND_H_
#include "../../../common/game_image.h"
class Sound {

public:
    SoundType sound;
    Position pos;
    Sound(): sound(SoundType::NONE) {}
    Sound(SoundType sound, const Position& pos): sound(sound), pos(pos) {}
    virtual ~Sound() = default;
};
#endif  // SOUND_H_