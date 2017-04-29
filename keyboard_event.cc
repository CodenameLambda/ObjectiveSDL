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

        TextEditingEvent::TextEditingEvent()
        : BuiltinEvent(), start(this->underlying_event.edit.start),
          length(this->underlying_event.edit.length) {
              this->underlying_event.edit.type = SDL_TEXTEDITING;
              this->underlying_event.edit.timestamp = 0;
              this->underlying_event.edit.windowID = 0;
              this->underlying_event.edit.text[0] = '\0';
              this->underlying_event.edit.start = 0;
              this->underlying_event.edit.length = 0;
        }

        TextEditingEvent::TextEditingEvent(const SDL_Event& ev)
        : BuiltinEvent(ev), start(this->underlying_event.edit.start),
          length(this->underlying_event.edit.length) {
        }

        TextEditingEvent::TextEditingEvent(SDL_Event&& ev)
        : BuiltinEvent(ev), start(this->underlying_event.edit.start),
          length(this->underlying_event.edit.length) {
        }

        TextEditingEvent::TextEditingEvent(std::string text, ssize_t start, ssize_t length)
        : TextEditingEvent() {
            this->text(text);
            this->start = start;
            this->length = length;
        }

        std::string TextEditingEvent::text() {
            return std::string(this->underlying_event.edit.text);
        }

        void TextEditingEvent::text(std::string s) {
            unsigned char i;
            for (i = 0; i < s.size() && i < 255; ++i) {
                this->underlying_event.edit.text[i] = s[i];
            }
            this->underlying_event.edit.text[i] = '\0';
        }
    }
}
