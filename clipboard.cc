#include "clipboard.hh"
#include <SDL.h>


namespace SDL {
    namespace clipboard {
        bool has_text() {
            return SDL_HasClipboardText() == SDL_TRUE;
        }

        void set_text(const std::string contents) {
            SDL_SetClipboardText(contents.c_str());
        }

        std::string get_text() {
            return SDL_GetClipboardText();
        }
    }
}
