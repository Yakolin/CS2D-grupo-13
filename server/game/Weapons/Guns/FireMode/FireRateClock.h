#ifndef FIRE_RATE_CLOCK_H_
#define FIRE_RATE_CLOCK_H_
#include <chrono>

using fire_rate_t = uint8_t;

class FireRateClock {
private:
    std::chrono::steady_clock::time_point last_shot_time;
    const fire_rate_t fire_rate;
    bool timer_started;

public:
    explicit FireRateClock(fire_rate_t fire_rate): fire_rate(fire_rate), timer_started(false) {}

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
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - last_shot_time);

        return elapsed.count() >= fire_rate;
    }
};

#endif  // FIRE_RATE_CLOCK_H_
