#ifndef TIMER_H_
#define TIMER_H_
#include <algorithm>
#include <chrono>
class Timer {
    using clock = std::chrono::steady_clock;
    int buy_duration = 0;
    int round_duration = 120 + buy_duration;  // En segundos

    int bomb_duration = 15;  // ??? deberia ir aca?
    bool round_started = false;
    bool bomb_activate = false;
    clock::time_point round_start_time;
    clock::time_point bomb_start_time;

public:
    Timer() = default;
    ~Timer() = default;
    void round_start() {
        round_start_time = clock::now();
        round_started = true;
    }
    void bomb_start() {
        bomb_start_time = clock::now();
        bomb_activate = true;
    }
    int get_time_buy() const {
        auto time =
                std::chrono::duration_cast<std::chrono::seconds>(clock::now() - round_start_time)
                        .count();
        return std::max(0, buy_duration - static_cast<int>(time));
    }
    int get_time_round() const {
        int round_real_time = (bomb_activate) ? bomb_duration : round_duration;
        clock::time_point time_start = (bomb_activate) ? bomb_start_time : round_start_time;
        auto time =
                std::chrono::duration_cast<std::chrono::seconds>(clock::now() - time_start).count();
        return std::max(0, round_real_time - static_cast<int>(time));
    }
    bool is_round_over() { return round_started && get_time_round() == 0; }
    bool is_time_buy() { return get_time_buy() > 0; }
};

#endif  // TIMER_H_
