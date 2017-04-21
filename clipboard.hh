#ifndef SDL_CLIPBOARD_HH
#define SDL_CLIPBOARD_HH

#include <string>


namespace SDL {
    namespace clipboard {
        bool has_text();
        void set_text(const std::string);
        std::string get_text();
    }
}

#endif
