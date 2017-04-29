#include "event.hh"

namespace SDL {
    const char* OtherEventType::what() const noexcept {
        return "The event doesn't contain the given type.";
    }

    Event::Event() {
    }

    Event::Event(const SDL_Event& ev) {
        this->underlying_event = ev;
    }

    Event::Event(SDL_Event&& ev) {
        this->underlying_event = ev;
    }

    SDL_Event& Event::get() {
        return this->underlying_event;
    }

    const SDL_Event& Event::get() const {
        return this->underlying_event;
    }

    template <typename R, typename D, typename T>
    std::chrono::duration<R, typename D::period> cast(T tp) {
        return std::chrono::duration_cast<std::chrono::duration<R, typename D::period>>(
            std::chrono::duration<R, std::chrono::milliseconds::period>(R(tp))
        );
    }

    std::chrono::system_clock::time_point Event::timestamp() const {
        using TP = std::chrono::time_point<std::chrono::system_clock>;
        return TP(cast<TP::rep, TP::duration, Uint32>(this->underlying_event.user.timestamp));
    }

    Window& Event::window() const {
        return *((Window*) nullptr);  // TODO
    }

    size_t Event::window_id() const {
        return this->underlying_event.user.windowID;
    }

    void Event::push() {
        SDL_PushEvent(&(this->underlying_event));
    }

    bool BuiltinEvent::Event::is_user_defined() const {
        return false;
    }

    namespace events {
        QuitEvent::QuitEvent() : BuiltinEvent() {
            this->underlying_event.quit.type = SDL_QUIT;
        }
    }
}
