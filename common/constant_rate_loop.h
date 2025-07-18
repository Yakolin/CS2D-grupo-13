#ifndef CONSTANT_RATE_LOOP_H
#define CONSTANT_RATE_LOOP_H
#include <functional>

class ConstantRateLoop {
private:
    const std::function<bool()> should_keep_running;
    const std::function<void()> func;  // Función sin parámetro de iteración

public:
    // Function that determines if we should keep running, function to execute each step
    ConstantRateLoop(const std::function<bool()>& keep_running_func,
                     const std::function<void()>& step_func);
    ~ConstantRateLoop();
    void execute();
};
#endif  // CONSTANT_RATE_LOOP_H
