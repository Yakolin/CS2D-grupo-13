#ifndef BURST_CLOCK_H_
#define BURST_CLOCK_H_

#include <chrono>

using burst_coldown_t = uint16_t;

class BurstClock {
private:
    std::chrono::steady_clock::time_point last_burst_time;
    const burst_coldown_t burst_cooldown;
    bool timer_started;

public:
    explicit BurstClock(burst_coldown_t cooldown): burst_cooldown(cooldown), timer_started(false) {}

    void start() {
        last_burst_time = std::chrono::steady_clock::now();
        timer_started = true;
    }

    void reset() { timer_started = false; }

    bool can_fire() {
        if (!timer_started) {
            return true;
        }

        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_burst_time);

        return elapsed.count() >= burst_cooldown;
    }
};
#endif  // BURST_CLOCK_H_
