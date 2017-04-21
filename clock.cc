#include "clock.hh"
#include <thread>


Clock::Clock() {
    last = std::chrono::system_clock::now();
    first = true;
}

std::chrono::milliseconds Clock::tick() {
    const auto current = std::chrono::system_clock::now();
    std::chrono::milliseconds delta = std::chrono::duration_cast<std::chrono::milliseconds>(
            current - this->last
    );
    this->last = current;
    return delta;
}

std::chrono::milliseconds Clock::tick(const float fps) {
    const auto delta = this->tick();
    const auto min_delta = std::chrono::duration<double>(1.0 / double(fps));
    const auto delta_delta = delta - min_delta;
    if (delta_delta > std::chrono::duration<double>(0.)) {
        std::this_thread::sleep_for(delta_delta);
        return std::chrono::duration_cast<std::chrono::milliseconds>(min_delta);
    } else {
        return delta;
    }
}
