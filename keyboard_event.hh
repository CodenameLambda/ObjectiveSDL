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

        class TextEditingEvent : public BuiltinEvent {
            public:
            Sint32& start;
            Sint32& length;

            TextEditingEvent();
            TextEditingEvent(const SDL_Event&);
            TextEditingEvent(SDL_Event&&);
            TextEditingEvent(std::string text, ssize_t start, ssize_t length);

            std::string text();
            void text(std::string);
        };
    }
}

#endif
