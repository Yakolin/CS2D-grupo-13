#ifndef SOUND_SHOOT_H_
#define SOUND_SHOOT_H_

#include "Sound.h"
class SoundShoot: public Sound {
    WeaponCode code;

public:
    explicit SoundShoot(WeaponCode code, Position& pos): Sound(SoundType::SHOOT, pos), code(code) {}
};
#endif  // SOUND_SHOOT_H_