#ifndef TYPE_H_
#define TYPE_H_

#include <string>
class TypesStates {
    public:
    typedef struct PlayerState
    {
        int id;
        int health;
        float position_x;
        float position_y;
        //int bullets;
        bool alive;
        //Por ahi hace falta mas cosas
    }player_state_t;

    typedef struct ObjectState{
        std::string type;
        float position_x;
        float position_y;
    }object_state_t;
};

#endif // TYPE_H_
