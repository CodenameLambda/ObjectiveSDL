#ifndef OBJSDL_CLOCK_HH
#define OBJSDL_CLOCK_HH

#include <chrono>


namespace SDL {
    class Clock {
        decltype(std::chrono::system_clock::now()) last;
        bool first;

        public:
        Clock();

        std::chrono::milliseconds tick();
        std::chrono::milliseconds tick(const float fps);
    };
}

#endif
