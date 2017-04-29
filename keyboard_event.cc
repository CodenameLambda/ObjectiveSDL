#include "keyboard_event.hh"


namespace SDL {
    namespace events {
        KeyboardEvent::KeyboardEvent()
        : BuiltinEvent(), repeat(this->underlying_event.key.repeat),
          key_symbol(this->underlying_event.key.keysym) {
              this->underlying_event.key.type = SDL_KEYDOWN;
              this->underlying_event.key.timestamp = 0;
              this->underlying_event.key.windowID = 0;
              this->underlying_event.key.state = SDL_PRESSED;
              this->underlying_event.key.repeat = 0;
        }

        KeyboardEvent::KeyboardEvent(const SDL_Event& ev)
        : BuiltinEvent(ev), repeat(this->underlying_event.key.repeat),
          key_symbol(this->underlying_event.key.keysym) {
        }

        KeyboardEvent::KeyboardEvent(SDL_Event&& ev)
        : BuiltinEvent(ev), repeat(this->underlying_event.key.repeat),
          key_symbol(this->underlying_event.key.keysym) {
        }

        KeyboardEvent::KeyboardEvent(
            const unsigned char repeat,
            const bool pressed,
            const SDL_Keysym key
        ) : KeyboardEvent() {
            this->repeat = repeat;
            this->pressed(pressed);
            this->key_symbol = key;
        }

        KeyboardEvent::KeyboardEvent(const bool pressed, const SDL_Keysym key)
        : KeyboardEvent(0, pressed, key) {
        }

        bool KeyboardEvent::pressed() {
            return this->underlying_event.key.state == SDL_PRESSED;
        }

        void KeyboardEvent::pressed(bool value) {
            this->underlying_event.key.state = value? SDL_PRESSED : SDL_RELEASED;
        }

        KeyPressedEvent::KeyPressedEvent(const unsigned char repeat, const SDL_Keysym key)
        : KeyboardEvent(repeat, true, key) {
        }

        KeyPressedEvent::KeyPressedEvent(const SDL_Keysym key) : KeyboardEvent(true, key) {
        }

        KeyReleasedEvent::KeyReleasedEvent() : KeyboardEvent() {
            this->pressed(false);
        }

        KeyReleasedEvent::KeyReleasedEvent(const SDL_Keysym key) : KeyboardEvent(false, key) {
        }
    }
}
