#ifndef OBJSDL_KEYBOARD_EVENT_HH
#define OBJSDL_KEYBOARD_EVENT_HH
#include "event.hh"

namespace SDL {
    namespace events {
        class KeyboardEvent : public BuiltinEvent {
            public:
            Uint8& repeat;
            SDL_Keysym& key_symbol;

            KeyboardEvent();
            KeyboardEvent(const SDL_Event& ev);
            KeyboardEvent(SDL_Event&& ev);
            KeyboardEvent(const unsigned char repeat, const bool pressed, const SDL_Keysym key);
            KeyboardEvent(const bool pressed, const SDL_Keysym key);
            bool pressed();
            void pressed(bool);
        };

        class KeyPressedEvent : public KeyboardEvent {
            public:
            using KeyboardEvent::KeyboardEvent;
            KeyPressedEvent(
                const unsigned char repeat,
                const bool pressed,
                const SDL_Keysym key
            ) = delete;
            KeyPressedEvent(const bool pressed, const SDL_Keysym key) = delete;
            KeyPressedEvent(const unsigned char repeat, const SDL_Keysym key);
            KeyPressedEvent(const SDL_Keysym key);
        };

        class KeyReleasedEvent : public KeyboardEvent {
            public:
            using KeyboardEvent::KeyboardEvent;
            KeyReleasedEvent();
            KeyReleasedEvent(
                const unsigned char repeat,
                const bool pressed,
                const SDL_Keysym key
            ) = delete;
            KeyReleasedEvent(const bool pressed, const SDL_Keysym key) = delete;
            KeyReleasedEvent(const SDL_Keysym key);
        };
    }
}

#endif
