#ifndef OBJSDL_CURSOR_HH
#define OBJSDL_CURSOR_HH

#include <SDL.h>
#include <initializer_list>
#include <string>
#include "geometry.hh"

struct Surface {
    // TODO: Remove in favour of the real surface class
    SDL_Surface* sdl_surface;
};

namespace SDL {
    enum class Pixel {
        _,  // transparent
        X,  // black
        O,  // white
        Z   // inverted or black, if not available
    };


    namespace cursor_pixels {
        extern Pixel _;
        extern Pixel X;
        extern Pixel O;
        extern Pixel Z;
    }


    class Cursor {
        SDL_Cursor* cursor;
        bool has_control;

        public:
        Cursor();  // default cursor (arrow)
        Cursor(Cursor&) = delete;  // freeing would be a nightmare...
        Cursor(Cursor&&);

        // the center is positioned relative to the top left
        Cursor(
            const std::initializer_list<std::initializer_list<Pixel>>,
            const Vector2S center={0, 0}
        );

        Cursor(
            const std::initializer_list<std::string>,
            const Vector2S center={0, 0}
        );

        Cursor(std::string, const Vector2S center={0, 0});

        Cursor(
            const std::string,
            size_t width,
            const Vector2S center={0, 0}
        );  // If you don't use newlines

        Cursor(Surface&, const Vector2S center={0, 0});

        private:
        Cursor(const SDL_SystemCursor);

        public:
        ~Cursor();

        static Cursor pointer;
        static Cursor i_beam;
        static Cursor wait;
        static Cursor crosshair;
        static Cursor wait_and_pointer;
        static Cursor arrow_nw_se;
        static Cursor arrow_ne_sw;
        static Cursor arrow_horizontal;
        static Cursor arrow_vertical;
        static Cursor arrow_cross;
        static Cursor slashed_circle;
        static Cursor hand;
    };
}

#endif
