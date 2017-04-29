#ifndef OBJSDL_WINDOW_EVENT_HH
#define OBJSDL_WINDOW_EVENT_HH
#include "event.hh"


namespace SDL {
    namespace events {
        Event* construct_window_event(SDL_Event ev);

        class WindowEvent : public BuiltinEvent {
            public:
            using BuiltinEvent::BuiltinEvent;

            size_t window_event_id;

            WindowEvent();
        };

        class WindowShownEvent : public WindowEvent {
            using WindowEvent::WindowEvent;
            size_t window_event_id = SDL_WINDOWEVENT_SHOWN;
        };

        class WindowHiddenEvent : public WindowEvent {
            using WindowEvent::WindowEvent;
            size_t window_event_id = SDL_WINDOWEVENT_HIDDEN;
        };

        class WindowExposedEvent : public WindowEvent {  // should be redrawn
            using WindowEvent::WindowEvent;
            size_t window_event_id = SDL_WINDOWEVENT_EXPOSED;
        };

        class WindowMovedEvent : public WindowEvent {
            public:
            using WindowEvent::WindowEvent;
            size_t window_event_id = SDL_WINDOWEVENT_MOVED;

            Sint32& x;
            Sint32& y;

            WindowMovedEvent();
            WindowMovedEvent(const SDL_Event& ev);
            WindowMovedEvent(SDL_Event&& ev);
            WindowMovedEvent(const ssize_t x, const ssize_t y);
        };

        class WindowResizedEvent : public WindowEvent {  // not for API call
            public:
            using WindowEvent::WindowEvent;
            size_t window_event_id = SDL_WINDOWEVENT_RESIZED;

            Sint32& w;
            Sint32& h;

            WindowResizedEvent();
            WindowResizedEvent(const SDL_Event& ev);
            WindowResizedEvent(SDL_Event&& ev);
            WindowResizedEvent(const size_t w, const size_t h);
        };

        class WindowSizeChangedEvent : public WindowEvent {
            public:
            using WindowEvent::WindowEvent;
            size_t window_event_id = SDL_WINDOWEVENT_SIZE_CHANGED;

            Sint32& w;
            Sint32& h;

            WindowSizeChangedEvent();
            WindowSizeChangedEvent(const SDL_Event& ev);
            WindowSizeChangedEvent(SDL_Event&& ev);
            WindowSizeChangedEvent(const size_t w, const size_t h);
        };

        class WindowMinimizedEvent : public WindowEvent {
            using WindowEvent::WindowEvent;
            size_t window_event_id = SDL_WINDOWEVENT_MINIMIZED;
        };

        class WindowMaximizedEvent : public WindowEvent {
            using WindowEvent::WindowEvent;
            size_t window_event_id = SDL_WINDOWEVENT_MAXIMIZED;
        };

        class WindowRestoredEvent : public WindowEvent {
            using WindowEvent::WindowEvent;
            size_t window_event_id = SDL_WINDOWEVENT_RESTORED;
        };

        class WindowGainedMouseFocusEvent : public WindowEvent {
            using WindowEvent::WindowEvent;
            size_t window_event_id = SDL_WINDOWEVENT_ENTER;
        };

        class WindowLostMouseFocusEvent : public WindowEvent {
            using WindowEvent::WindowEvent;
            size_t window_event_id = SDL_WINDOWEVENT_LEAVE;
        };

        class WindowGainedKeyboardFocusEvent : public WindowEvent {
            using WindowEvent::WindowEvent;
            size_t window_event_id = SDL_WINDOWEVENT_FOCUS_GAINED;
        };

        class WindowLostKeyboardFocusEvent : public WindowEvent {
            using WindowEvent::WindowEvent;
            size_t window_event_id = SDL_WINDOWEVENT_FOCUS_LOST;
        };

        class WindowClosedEvent : public WindowEvent {
            using WindowEvent::WindowEvent;
            size_t window_event_id = SDL_WINDOWEVENT_CLOSE;
        };

        class WindowFocusOfferedEvent : public WindowEvent {
            using WindowEvent::WindowEvent;
            size_t window_event_id = SDL_WINDOWEVENT_TAKE_FOCUS;

            void take() const;
        };

        class WindowHitTestEvent : public WindowEvent {
            using WindowEvent::WindowEvent;
            size_t window_event_id = SDL_WINDOWEVENT_HIT_TEST;
        };

        extern const std::unordered_map<size_t, std::function<Event*(SDL_Event)>> window_event_types;
    }
}
#endif
