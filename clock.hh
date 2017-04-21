#ifndef SDL_CLOCK_HH
#define SDL_CLOCK_HH

#include <chrono>


class Clock {
    decltype(std::chrono::system_clock::now()) last;
    bool first;

    public:
    Clock();

    std::chrono::milliseconds tick();
    std::chrono::milliseconds tick(const float fps);
};

#endif
