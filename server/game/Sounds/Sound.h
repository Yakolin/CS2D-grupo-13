#ifndef SOUND_H_
#define SOUND_H_
#include "../../../common/game_image.h"
class Sound {

public:
    SoundType sound;
    Sound(): sound(SoundType::NONE) {}
    Sound(SoundType sound): sound(sound) {}
    virtual ~Sound() = default;
};
#endif  // SOUND_H_