#ifndef TIMER_H_
#define TIMER_H_
#include <algorithm>
#include <chrono>

#include "Config/GameConfig.h"
enum class TimerState { NONE, ROUND_START, BOMB_ACTIVATED, ENDING_TIME };
class Timer {
    using clock = std::chrono::steady_clock;
    int buy_duration;
    int round_duration;
    int bomb_duration;
    int ending_duration;
    TimerState state = TimerState::NONE;
    clock::time_point round_start_time;
    clock::time_point bomb_start_time;
    clock::time_point ending_start_time;
    GameConfig::TimerConfig timer_config;

    int get_time_buy() const {
        auto time =
                std::chrono::duration_cast<std::chrono::seconds>(clock::now() - round_start_time)
                        .count();
        return std::max(0, buy_duration - static_cast<int>(time));
    }

public:
    explicit Timer(GameConfig::TimerConfig& timer_config): timer_config(timer_config) {
        buy_duration = timer_config.time_buy;
        bomb_duration = timer_config.time_bomb;
        round_duration = timer_config.time_round + buy_duration;
        ending_duration = timer_config.time_ending;
    }
    ~Timer() = default;
    void round_start() {
        round_start_time = clock::now();
        state = TimerState::ROUND_START;
    }
    void round_end() {
        ending_start_time = clock::now();
        state = TimerState::ENDING_TIME;
    }
    void bomb_start() {
        bomb_start_time = clock::now();
        state = TimerState::BOMB_ACTIVATED;
    }
    int get_time_round() const {
        int round_real_time = (state == TimerState::BOMB_ACTIVATED) ? bomb_duration :
                              (state == TimerState::ENDING_TIME)    ? ending_duration :
                                                                      round_duration;
        clock::time_point time_start = (state == TimerState::BOMB_ACTIVATED) ? bomb_start_time :
                                       (state == TimerState::ENDING_TIME)    ? ending_start_time :
                                                                               round_start_time;
        auto time =
                std::chrono::duration_cast<std::chrono::seconds>(clock::now() - time_start).count();
        return std::max(0, round_real_time - static_cast<int>(time));
    }
    TimerState get_state() { return state; }
    bool is_round_over() { return state == TimerState::ROUND_START && get_time_round() == 0; }
    bool is_time_to_buy() { return get_time_buy() > 0; }
};

#endif  // TIMER_H_
