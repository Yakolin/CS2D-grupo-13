#ifndef WEAPON_H_
#define WEAPON_H_
class Weapon {
public:
    Weapon() = default;
    ~Weapon() = default;
    virtual void fire() = 0;  // Recordatorio de este = 0. Significa que es puro
    virtual void reload() = 0;
};
#endif  //  WEAPON_H_
