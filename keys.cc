#include "keys.hh"


namespace SDL {
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

    Key key_from_name(const std::string& s) {
        return Key(SDL_GetKeyFromName(s.c_str()));
    }

    Key key_from_name(std::string&& s) {
        return Key(SDL_GetKeyFromName(s.c_str()));
    }

    Key key_from_scankey(const ScanKey key) {
        return Key(SDL_GetKeyFromScancode(SDL_Scancode(key)));
    }

    std::string get_key_name(const Key key) {
        return SDL_GetKeyName(SDL_Keycode(key));
    }

    // TODO: Window& get_keyboard_focus()
    
    SDL_Keymod get_modifiers() {
        return SDL_GetModState();
    }

    void set_modifiers(SDL_Keymod keymod) {
        SDL_SetModState(keymod);
    }

    ScanKey get_scankey_from_key(const Key key) {
        return ScanKey(SDL_GetScancodeFromKey(SDL_Keycode(key)));
    }

    ScanKey get_scankey_from_name(const std::string& s) {
        return ScanKey(SDL_GetScancodeFromName(s.c_str()));
    }

    ScanKey get_scankey_from_name(std::string&& s) {
        return ScanKey(SDL_GetScancodeFromName(s.c_str()));
    }

    std::string get_scankey_name(const ScanKey key) {
        return SDL_GetScancodeName(SDL_Scancode(key));
    }

    bool has_screen_keyboard_support() {
        return SDL_HasScreenKeyboardSupport() == SDL_TRUE;
    }

    // TODO: bool screen_keyboard_shown(Window& window)
    
    bool text_input_active() {
        return SDL_IsTextInputActive() == SDL_TRUE;
    }

    void start_text_input() {
        SDL_StartTextInput();
    }

    void stop_text_input() {
        SDL_StopTextInput();
    }

    void set_text_input_rectangle(const RectangleI rect) {
        SDL_Rect sdl_rect;
        sdl_rect.x = x(rect.position1);
        sdl_rect.y = y(rect.position1);
        auto size = rect.position2 - rect.position1;
        sdl_rect.w = x(size);
        sdl_rect.h = y(size);
        SDL_SetTextInputRect(&sdl_rect);
    }

    boost::dynamic_bitset<> get_keyboard_state() {
        const Uint8* state = SDL_GetKeyboardState(NULL);
        boost::dynamic_bitset<> out{sizeof(state) / sizeof(state[0])};
        for (size_t i = 0; i < out.size(); ++i)
            out[i] = state[i];
        return out;
    }
}
