#include "constant_rate_loop.h"

#include <chrono>
#include <thread>

using namespace std::chrono;

#define FPS 40
#define FRAME_INTERVAL static_cast<int>((1.0f / FPS) * 1000)
#define FRAME_RATE std::chrono::milliseconds(FRAME_INTERVAL)

ConstantRateLoop::ConstantRateLoop(std::atomic<bool>& k_r,
                                   const std::function<void(unsigned int)>& f):
        keep_running(k_r), func(f) {}

ConstantRateLoop::~ConstantRateLoop() {}

void ConstantRateLoop::execute() {
    using clock = std::chrono::steady_clock;
    auto t1 = clock::now();
    int it = 0;

    while (keep_running.load()) {
        func(it);
        auto t2 = clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
        auto rest = FRAME_RATE - elapsed;

        if (rest < std::chrono::milliseconds(0)) {
            // Calculate how much time is behind and correct for the lost time
            auto behind = -rest;
            rest = std::chrono::milliseconds(FRAME_INTERVAL - (behind.count() % FRAME_INTERVAL));
            auto lost = behind + rest;
            t1 += std::chrono::milliseconds(lost.count());
            it += static_cast<int>(lost.count() / FRAME_INTERVAL);
        }
        std::this_thread::sleep_for(rest);
        t1 += FRAME_RATE;
        it++;
    }
}