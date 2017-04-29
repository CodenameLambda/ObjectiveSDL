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

        bool KeyboardEvent::pressed() const {
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

        std::string TextEditingEvent::text() const {
            return std::string(this->underlying_event.edit.text);
        }

        void TextEditingEvent::text(std::string s) {
            unsigned char i;
            for (i = 0; i < s.size() && i < 31; ++i) {
                this->underlying_event.edit.text[i] = s[i];
            }
            this->underlying_event.edit.text[i] = '\0';
        }

        unsigned char TextEditingEvent::new_length() const {
            unsigned char l;
            for (l = 0; l < 31; ++l) {
                if (this->underlying_event.edit.text[l] == '\0')
                    return l;
            }
            return 31;
        }

        ssize_t TextEditingEvent::length_delta() const {
            return ssize_t(this->new_length()) - ssize_t(this->length);
        }

        TextInputEvent::TextInputEvent() : BuiltinEvent() {
            this->underlying_event.text.type = SDL_TEXTINPUT;
            this->underlying_event.text.timestamp = 0;
            this->underlying_event.text.windowID = 0;
            this->underlying_event.text.text[0] = '\0';
        }

        TextInputEvent::TextInputEvent(std::string text) : BuiltinEvent() {
            this->text(text);
        }

        std::string TextInputEvent::text() {
            return std::string(this->underlying_event.text.text);
        }

        void TextInputEvent::text(std::string s) {
            unsigned char i;
            for (i = 0; i < s.size() && i < 31; ++i) {
                this->underlying_event.text.text[i] = s[i];
            }
            this->underlying_event.edit.text[i] = '\0';
        }
    }
}
