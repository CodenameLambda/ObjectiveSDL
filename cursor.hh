#ifndef OBJSDL_CURSOR_HH
#define OBJSDL_CURSOR_HH

#include <SDL.h>
#include <initializer_list>
#include <string>

struct Vector2s {
    // TODO: Remove in favour of the real vector class group
    size_t x;
    size_t y;

    const size_t& operator[](const size_t index) const;
};

struct Surface {
    // TODO: Remove in favour of the real surface class
    SDL_Surface* sdl_surface;
};

namespace SDL {
    namespace _implementation {
        namespace cursor {
            enum Pixel {
                _,  // transparent
                X,  // black
                O,  // white
                Z   // inverted or black, if not available
            };
        }
    }


    namespace cursor_pixels {
        extern _implementation::cursor::Pixel _;
        extern _implementation::cursor::Pixel X;
        extern _implementation::cursor::Pixel O;
        extern _implementation::cursor::Pixel Z;
    }


    class Cursor {
        SDL_Cursor* cursor;
        bool has_control;

        public:
        Cursor();  // default cursor (arrow)
        Cursor(Cursor&) = delete;  // freeing would be a nightmare...
        Cursor(Cursor&&);

        using Pixel = _implementation::cursor::Pixel;

        // the center is positioned relative to the top left
        Cursor(
            const std::initializer_list<std::initializer_list<Pixel>>,
            const Vector2s center={0, 0}
        );

        Cursor(
            const std::initializer_list<std::string>,
            const Vector2s center={0, 0}
        );

        Cursor(std::string, const Vector2s center={0, 0});

        Cursor(
            const std::string,
            size_t width,
            const Vector2s center={0, 0}
        );  // If you don't use newlines

        Cursor(Surface&, const Vector2s center={0, 0});

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
