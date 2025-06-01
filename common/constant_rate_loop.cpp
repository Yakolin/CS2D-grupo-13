#include "constant_rate_loop.h"

#include <chrono>
#include <thread>

using namespace std::chrono;

#define FPS 40
#define FRAME_INTERVAL static_cast<int>((1.0f / FPS) * 1000)
#define FRAME_RATE std::chrono::milliseconds(FRAME_INTERVAL)

ConstantRateLoop::ConstantRateLoop(const std::function<bool()>& keep_running_func,
                                   const std::function<void()>& step_func):
        should_keep_running(keep_running_func), func(step_func) {}

ConstantRateLoop::~ConstantRateLoop() {}

void ConstantRateLoop::execute() {
    using clock = std::chrono::steady_clock;
    auto t1 = clock::now();
    unsigned int it = 0;
    while (should_keep_running()) {
        func();
        auto t2 = clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
        auto rest = FRAME_RATE - elapsed;
        if (rest < std::chrono::milliseconds(0)) {

            auto behind = -rest;
            rest = std::chrono::milliseconds(FRAME_INTERVAL - (behind.count() % FRAME_INTERVAL));
            auto lost = behind + rest;
            t1 += std::chrono::milliseconds(lost.count());
            it += static_cast<unsigned int>(lost.count() / FRAME_INTERVAL);
        }
        std::this_thread::sleep_for(rest);
        t1 += FRAME_RATE;
        it++;
    }
}
