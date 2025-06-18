#ifndef TIMER_ACTIONS_H_
#define TIMER_ACTIONS_H_
#include <chrono>
class TimerActions {
    using clock = std::chrono::steady_clock;
    clock::time_point start_time;
    // Counting sirve para mantener una cuenta de los segundos pasados entre llamadas
    // Es util para hacer cuentas regresivas si se mantienen botones por ejemplo
    clock::time_point counting;
    int wanted_timing;  // Aca en milisigundos

public:
    explicit TimerActions(int wanted_timing): wanted_timing(wanted_timing) {}
    void start() { start_time = clock::now(); }
    void start_counting() { counting = clock::now(); }
    bool elapsed_time() const {
        auto now = clock::now();
        auto passed =
                std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count();
        return passed >= wanted_timing;
    }
    float time_since_start() const {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> diff = now - start_time;
        return diff.count();
    }
    float get_elapsed() {
        auto now = clock::now();
        auto passed =
                std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count();
        return passed;
    }
    float get_counting() {
        auto now = clock::now();
        auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(now - counting).count();
        return passed;
    }
};

#endif  // TIMER_ACTIONS_H_
