#ifndef TIMER_H_
#define TIMER_H_
#include <algorithm>
#include <chrono>
class Timer {
    using clock = std::chrono::steady_clock;
    int buy_duration = 5;
    int round_duration = 16 + buy_duration;  // En segundos

    int bomb_duration = 15;  // ??? deberia ir aca?
    bool round_started = false;
    clock::time_point round_start_time;

public:
    Timer() = default;
    ~Timer() = default;
    void round_start() {
        round_start_time = clock::now();
        round_started = true;
    }
    int get_time_buy() const {
        auto time =
                std::chrono::duration_cast<std::chrono::seconds>(clock::now() - round_start_time)
                        .count();
        return std::max(0, buy_duration - static_cast<int>(time));
    }
    int get_time_round() const {
        auto time =
                std::chrono::duration_cast<std::chrono::seconds>(clock::now() - round_start_time)
                        .count();
        return std::max(0, round_duration - static_cast<int>(time));
    }
    bool is_round_over() { return round_started && get_time_round() == 0; }
    bool is_time_buy() { return get_time_buy() > 0; }
};

#endif  // TIMER_H_
