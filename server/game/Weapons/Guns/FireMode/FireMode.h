#ifndef FIRE_MODE_H
#define FIRE_MODE_H


class FireMode {
public:
    virtual ~FireMode() = default;
    virtual bool can_fire() = 0;
    virtual bool can_fire_burst() = 0;
};


#endif  // !FIRE_MODE_H