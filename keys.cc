#include "keys.hh"


namespace SDL {
    namespace events {
        KeyCombination::KeyCombination(const SDL_Keysym keysym) {
            this->sdl_keysym = keysym;
        }

        KeyCombination::KeyCombination(const Uint16 modifiers, const ScanKey key) {
            this->scan_key(key);
            this->sdl_keysym.mod = modifiers;
        }

        KeyCombination::KeyCombination(const Uint16 modifiers, const Key key) {
            this->key(key);
            this->sdl_keysym.mod = modifiers;
        }

        KeyCombination::KeyCombination(const ScanKey key) : KeyCombination(0, key) {
        }

        KeyCombination::KeyCombination(const Key key) : KeyCombination(0, key) {
        }

        bool KeyCombination::modifier(const Modifier m) const {
            return this->sdl_keysym.mod & Uint16(m);
        }

        void KeyCombination::modifier(const Modifier m, const bool value) {
            if (this->modifier(m) != value)
                this->sdl_keysym.mod = this->sdl_keysym.mod ^ Uint16(m);
        }

        ScanKey KeyCombination::scan_key() const {
            return ScanKey(this->sdl_keysym.scancode);
        }

        void KeyCombination::scan_key(const ScanKey key) {
            this->sdl_keysym.scancode = SDL_Scancode(key);
            this->sdl_keysym.sym = SDL_GetKeyFromScancode(SDL_Scancode(key));
        }

        Key KeyCombination::key() const {
            return Key(this->sdl_keysym.sym);
        }

        void KeyCombination::key(const Key key) {
            this->sdl_keysym.sym = SDL_Keycode(key);
            this->sdl_keysym.scancode = SDL_GetScancodeFromKey(SDL_Keycode(key));
        }
    }
}
