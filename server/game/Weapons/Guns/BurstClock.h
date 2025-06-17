#ifndef BURST_CLOCK_H_
#define BURST_CLOCK_H_

#include <chrono>
class BurstClock {
private:
    std::chrono::steady_clock::time_point start_time;

public:
    BurstClock() { start(); }

    void start() { start_time = std::chrono::steady_clock::now(); }

    bool elapsed(float seconds) const {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> diff = now - start_time;
        return diff.count() >= seconds;
    }

    float time_since_start() const {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> diff = now - start_time;
        return diff.count();
    }
};
#endif  // BURST_CLOCK_H_