#ifndef SOUND_SHOOT_H_
#define SOUND_SHOOT_H_

#include "Sound.h"
class SoundShoot: public Sound {
public:
    WeaponCode code;
    explicit SoundShoot(WeaponCode code): Sound(SoundType::SHOOT), code(code) {}
};
#endif  // SOUND_SHOOT_H_