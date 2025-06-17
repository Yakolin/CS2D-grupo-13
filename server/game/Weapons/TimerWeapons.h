#ifndef TIMER_WEAPONS_H_
#define TIMER_WEAPONS_H_
#include <chrono>
class TimerWeapons {
    using clock = std::chrono::steady_clock;
    clock::time_point start_time;
    int fire_rate;  // Aca en milisigundos

public:
    explicit TimerWeapons(int fire_rate): fire_rate(fire_rate) {}
    void start() { start_time = clock::now(); }
    bool can_shoot() {
        auto now = clock::now();
        auto passed =
                std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count();
        return passed >= fire_rate;
    }
};
#endif  // TIMER_WEAPONS_H_
