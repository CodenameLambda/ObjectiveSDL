#include "window_event.hh"


namespace SDL {
    namespace events {
        Event* construct_window_event(SDL_Event ev) {
            return window_event_types.at(ev.window.type)(ev);
        }

        WindowEvent::WindowEvent()
        : BuiltinEvent() {
            auto& e = this->underlying_event.window;
            e.type = SDL_WINDOWEVENT;
            e.timestamp = 0;
            e.windowID = 0;
            e.event = this->window_event_id;
            e.data1 = 0;
            e.data2 = 0;
        }

        WindowMovedEvent::WindowMovedEvent()
        : WindowEvent(), x(underlying_event.window.data1), y(underlying_event.window.data2) {
        }

        WindowMovedEvent::WindowMovedEvent(const SDL_Event& ev)
        : WindowEvent(ev), x(underlying_event.window.data1), y(underlying_event.window.data2) {
        }

        WindowMovedEvent::WindowMovedEvent(SDL_Event&& ev)
        : WindowEvent(ev), x(underlying_event.window.data1), y(underlying_event.window.data2) {
        }

        WindowMovedEvent::WindowMovedEvent(const ssize_t x, const ssize_t y) : WindowMovedEvent() {
            this->x = x;
            this->y = y;
        }

        WindowResizedEvent::WindowResizedEvent()
        : WindowEvent(), w(underlying_event.window.data1), h(underlying_event.window.data2) {
        }

        WindowResizedEvent::WindowResizedEvent(const SDL_Event& ev)
        : WindowEvent(ev), w(underlying_event.window.data1), h(underlying_event.window.data2) {
        }

        WindowResizedEvent::WindowResizedEvent(SDL_Event&& ev)
        : WindowEvent(ev), w(underlying_event.window.data1), h(underlying_event.window.data2) {
        }

        WindowResizedEvent::WindowResizedEvent(const size_t w, const size_t h)
        : WindowResizedEvent() {
            this->w = w;
            this->h = h;
        }

        WindowSizeChangedEvent::WindowSizeChangedEvent()
        : WindowEvent(), w(underlying_event.window.data1), h(underlying_event.window.data2) {
        }

        WindowSizeChangedEvent::WindowSizeChangedEvent(const SDL_Event& ev)
        : WindowEvent(ev), w(underlying_event.window.data1), h(underlying_event.window.data2) {
        }

        WindowSizeChangedEvent::WindowSizeChangedEvent(SDL_Event&& ev)
        : WindowEvent(ev), w(underlying_event.window.data1), h(underlying_event.window.data2) {
        }

        WindowSizeChangedEvent::WindowSizeChangedEvent(const size_t w, const size_t h)
        : WindowSizeChangedEvent() {
            this->w = w;
            this->h = h;
        }

        const std::unordered_map<size_t, std::function<Event*(SDL_Event)>> window_event_types {
            {SDL_WINDOWEVENT_SHOWN, [](SDL_Event e){ return new WindowShownEvent(e); }},
            {SDL_WINDOWEVENT_HIDDEN, [](SDL_Event e){ return new WindowHiddenEvent(e); }},
            {SDL_WINDOWEVENT_EXPOSED, [](SDL_Event e){ return new WindowExposedEvent(e); }},
            {SDL_WINDOWEVENT_MOVED, [](SDL_Event e){ return new WindowMovedEvent(e); }},
            {SDL_WINDOWEVENT_RESIZED, [](SDL_Event e){ return new WindowResizedEvent(e); }},
            {SDL_WINDOWEVENT_SIZE_CHANGED, [](SDL_Event e){ return new WindowSizeChangedEvent(e); }},
            {SDL_WINDOWEVENT_MINIMIZED, [](SDL_Event e){ return new WindowMinimizedEvent(e); }},
            {SDL_WINDOWEVENT_MAXIMIZED, [](SDL_Event e){ return new WindowMaximizedEvent(e); }},
            {SDL_WINDOWEVENT_RESTORED, [](SDL_Event e){ return new WindowRestoredEvent(e); }},
            {SDL_WINDOWEVENT_ENTER, [](SDL_Event e){ return new WindowGainedMouseFocusEvent(e); }},
            {SDL_WINDOWEVENT_LEAVE, [](SDL_Event e){ return new WindowLostMouseFocusEvent(e); }},
            {SDL_WINDOWEVENT_FOCUS_GAINED, [](SDL_Event e){
                    return new WindowGainedKeyboardFocusEvent(e);
            }},
            {SDL_WINDOWEVENT_FOCUS_LOST, [](SDL_Event e){
                    return new WindowLostKeyboardFocusEvent(e);
            }},
            {SDL_WINDOWEVENT_CLOSE, [](SDL_Event e){ return new WindowClosedEvent(e); }},
            {SDL_WINDOWEVENT_TAKE_FOCUS, [](SDL_Event e){ return new WindowFocusOfferedEvent(e); }},
            {SDL_WINDOWEVENT_HIT_TEST, [](SDL_Event e){ return new WindowHitTestEvent(e); }}
        };
    }
}
