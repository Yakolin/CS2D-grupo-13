#ifndef CONSTANT_RATE_LOOP_H
#define CONSTANT_RATE_LOOP_H

#include <atomic>
#include <functional>

class ConstantRateLoop {
private:
    std::atomic<bool>& keep_running;
    const std::function<void(int)> func;

public:
    // Keep running, rate, function
    ConstantRateLoop(std::atomic<bool>& k_r, const std::function<void(unsigned int)>& f);
    ~ConstantRateLoop();

    void execute();
};

#endif  // CONSTANT_RATE_LOOP_H