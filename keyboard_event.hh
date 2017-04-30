#ifndef OBJSDL_KEYBOARD_EVENT_HH
#define OBJSDL_KEYBOARD_EVENT_HH
#include "event.hh"

#include "keys.hh"

namespace SDL {
    namespace events {
        class KeyboardRelatedEvent : public BuiltinEvent {
            using BuiltinEvent::BuiltinEvent;
        };

        class KeyboardEvent : public KeyboardRelatedEvent {
            public:
            Uint8& repeat;

            KeyboardEvent();
            KeyboardEvent(const SDL_Event& ev);
            KeyboardEvent(SDL_Event&& ev);
            KeyboardEvent(
                const unsigned char repeat,
                const bool pressed,
                const KeyCombination key
            );
            KeyboardEvent(const bool pressed, const KeyCombination key);
            bool pressed() const;
            void pressed(const bool);

            KeyCombination key() const;
            void key(const KeyCombination);
        };

        class KeyPressedEvent : public KeyboardEvent {
            public:
            using KeyboardEvent::KeyboardEvent;
            KeyPressedEvent(
                const unsigned char repeat,
                const bool pressed,
                const KeyCombination key
            ) = delete;
            KeyPressedEvent(const bool pressed, const KeyCombination key) = delete;
            KeyPressedEvent(const unsigned char repeat, const KeyCombination key);
            KeyPressedEvent(const KeyCombination key);
        };

        class KeyReleasedEvent : public KeyboardEvent {
            public:
            using KeyboardEvent::KeyboardEvent;
            KeyReleasedEvent();
            KeyReleasedEvent(
                const unsigned char repeat,
                const bool pressed,
                const KeyCombination key
            ) = delete;
            KeyReleasedEvent(const bool pressed, const KeyCombination key) = delete;
            KeyReleasedEvent(const KeyCombination key);
        };

        class TextInputRelatedEvent : public KeyboardRelatedEvent {
            using KeyboardRelatedEvent::KeyboardRelatedEvent;
        };

        class TextEditingEvent : public TextInputRelatedEvent {
            public:
            Sint32& start;
            Sint32& length;

            TextEditingEvent();
            TextEditingEvent(const SDL_Event&);
            TextEditingEvent(SDL_Event&&);
            TextEditingEvent(std::string text, ssize_t start, ssize_t length);

            std::string text() const;
            void text(std::string);

            unsigned char new_length() const;
            ssize_t length_delta() const;
        };

        class TextInputEvent : public TextInputRelatedEvent {
            public:
            using TextInputRelatedEvent::TextInputRelatedEvent;
            TextInputEvent();
            TextInputEvent(std::string text);

            std::string text();
            void text(const std::string&);
        };
    }
}

#endif
