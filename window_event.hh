#ifndef OBJSDL_WINDOW_EVENT_HH
#define OBJSDL_WINDOW_EVENT_HH
#include "event.hh"


namespace SDL {
    namespace events {
        Event* construct_window_event(SDL_Event ev);

        class WindowEvent : public BuiltinEvent {
            protected:
            WindowEvent(unsigned char event_id);

            public:
            using BuiltinEvent::BuiltinEvent;

            WindowEvent();
        };

        class WindowShownEvent : public WindowEvent {
            using WindowEvent::WindowEvent;
            WindowShownEvent();
        };

        class WindowHiddenEvent : public WindowEvent {
            using WindowEvent::WindowEvent;
            WindowHiddenEvent();
        };

        class WindowExposedEvent : public WindowEvent {  // should be redrawn
            using WindowEvent::WindowEvent;
            WindowExposedEvent();
        };

        class WindowMovedEvent : public WindowEvent {
            public:
            using WindowEvent::WindowEvent;

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

            Sint32& w;
            Sint32& h;

            WindowSizeChangedEvent();
            WindowSizeChangedEvent(const SDL_Event& ev);
            WindowSizeChangedEvent(SDL_Event&& ev);
            WindowSizeChangedEvent(const size_t w, const size_t h);
        };

        class WindowMinimizedEvent : public WindowEvent {
            using WindowEvent::WindowEvent;
            public:
            WindowMinimizedEvent();
        };

        class WindowMaximizedEvent : public WindowEvent {
            using WindowEvent::WindowEvent;
            public:
            WindowMaximizedEvent();
        };

        class WindowRestoredEvent : public WindowEvent {
            using WindowEvent::WindowEvent;
            public:
            WindowRestoredEvent();
        };

        class WindowGainedMouseFocusEvent : public WindowEvent {
            using WindowEvent::WindowEvent;
            public:
            WindowGainedMouseFocusEvent();
        };

        class WindowLostMouseFocusEvent : public WindowEvent {
            using WindowEvent::WindowEvent;
            public:
            WindowLostMouseFocusEvent();
        };

        class WindowGainedKeyboardFocusEvent : public WindowEvent {
            using WindowEvent::WindowEvent;
            public:
            WindowGainedKeyboardFocusEvent();
        };

        class WindowLostKeyboardFocusEvent : public WindowEvent {
            using WindowEvent::WindowEvent;
            public:
            WindowLostKeyboardFocusEvent();
        };

        class WindowClosedEvent : public WindowEvent {
            using WindowEvent::WindowEvent;
            public:
            WindowClosedEvent();
        };

        class WindowFocusOfferedEvent : public WindowEvent {
            using WindowEvent::WindowEvent;

            public:
            WindowFocusOfferedEvent();

            void take() const;
        };

        class WindowHitTestEvent : public WindowEvent {
            using WindowEvent::WindowEvent;
            public:
            WindowHitTestEvent();
        };

        extern const std::unordered_map<unsigned char, std::function<Event*(SDL_Event)>> window_event_types;
    }
}
#endif
