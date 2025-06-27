#ifndef FIRE_RATE_CLOCK_H_
#define FIRE_RATE_CLOCK_H_
#include <chrono>

using timer_fire_t = uint16_t;

class FireRateClock {
private:
    std::chrono::steady_clock::time_point last_shot_time;
    const timer_fire_t timer_fire;
    bool timer_started;

public:
    explicit FireRateClock(timer_fire_t timer_fire): timer_fire(timer_fire), timer_started(false) {}

    void start() {
        last_shot_time = std::chrono::steady_clock::now();
        timer_started = true;
    }

    void reset() { timer_started = false; }

    bool can_fire() {
        if (!timer_started) {
            return true;  // Primera vez o después de reset
        }

        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_shot_time);

        return elapsed.count() >= timer_fire;
    }
};

#endif  // FIRE_RATE_CLOCK_H_
