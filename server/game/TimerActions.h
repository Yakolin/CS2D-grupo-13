#ifndef TIMER_ACTIONS_H_
#define TIMER_ACTIONS_H_
#include <chrono>
class TimerActions {
    using clock = std::chrono::steady_clock;
    clock::time_point start_time;
    int wanted_timing;  // Aca en milisigundos

public:
    explicit TimerActions(int wanted_timing): wanted_timing(wanted_timing) {}
    void start() { start_time = clock::now(); }
    bool elapsed_time() const {
        auto now = clock::now();
        auto passed =
                std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count();
        return passed >= wanted_timing;
    }
};

#endif  // TIMER_ACTIONS_H_
