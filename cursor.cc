#include "cursor.hh"
#include <tuple>
#include <cmath>
#include <vector>


size_t& Vector2s::operator[](size_t index) {
    if (index == 0)
        return this->x;
    else
        return this->y;
}


namespace SDL {
    namespace _implementation {
        namespace cursor {
            Pixel char_to_pixel(char c) {
                switch (c) {
                    case 'X':
                        return Pixel::X;
                    case 'O':
                    case '.':
                        return Pixel::O;
                    case 'Z':
                        return Pixel::Z;
                    default:
                        return Pixel::_;
                }
            }

            std::vector<std::string> split(std::string s) {
                std::vector<std::string> out;
                std::string current = "";
                for (const char c : s)
                    if (c == '\n') {
                        out.push_back(current);
                        current = "";
                    } else
                        current += c;
                out.push_back(current);
                return out;
            }
        }
    }

    template <typename T>
    SDL_Cursor* string_list_to_cursor(T l, Vector2s c) {
        auto current_line = l.begin();
        auto current_element = current_line->begin();

        return build_cursor(
            get_size(l),
            c,
            line_walker(current_line, current_element, l),
            [&](bool first) -> std::pair<bool, _implementation::cursor::Pixel> {
                if (!first)
                    ++ current_element;
                if (current_element == current_line->end())
                    return {true, _implementation::cursor::Pixel::_};
                else {
                    return {false, _implementation::cursor::char_to_pixel(*current_element)};
                }
            }
        );
    }

    template <typename T>
    Vector2s get_size(T container) {
        size_t width = 0;
        for (const auto& i : container) {
            size_t local_width = i.size();
            if (local_width > width)
                width = local_width;
        }
        if (width % 8 != 0)  // fix the width to be a multiple of 8.
            width = ((width >> 3) + 1) << 3;
        size_t height = container.size();
        if (height % 8 != 0)  // fix the height to be a multiple of 8
            height = ((height >> 3) + 1) << 3;
        // Are the same restrictions valid for the height of the cursor as for the width?
        
        return {width, height};
    }

    template <typename T, typename U, typename V>
    auto line_walker(T& iterator, U& sub_iterator, V& container) {
        return [=](bool first) mutable -> bool {
            if (!first) {
                ++ iterator;
                if (iterator == container.end())
                    return true;
                else {
                    sub_iterator = iterator->begin();
                    return false;
                }
            } else {
                return iterator == container.end();
            }
        };
    }

    template <typename T, typename U>
    SDL_Cursor* build_cursor(Vector2s s, Vector2s c, T next_line, U next_element) {
        // U has the form std::pair<bool, Pixel>(),
        // where the first entry is true if the iterator has iterated throug all elements
        // T only returns if there is a next line or not
        Uint8 data[size_t(s[0] * s[1] / 8)];
        Uint8 mask[size_t(s[0] * s[1] / 8)];

        size_t index = -1;  // equals max_value(size_t), but gets wrapped when incremented.
        // col is 0 at first, so there is no problem.
        
        bool done = next_line(true);

        while (!done) {
            size_t col = 0;
            bool line_done;
            Cursor::Pixel i;
            std::tie(line_done, i) = next_element(true);

            while (!line_done) {
                if (col % 8 != 0) {  // we write the next bit in the current byte
                    data[index] <<= 1;
                    mask[index] <<= 1;
                } else {  // we start the next byte
                    ++ index;
                    data[index] = mask[index] = 0;
                }
                ++ col;

                switch (i) {
                    case Cursor::Pixel::_:
                        break;
                    case Cursor::Pixel::X:
                        data[index] += 1;  // sets the last bit to one.
                    case Cursor::Pixel::O:
                        mask[index] += 1;
                        break;
                    case Cursor::Pixel::Z:
                        data[index] += 1;
                        break;
                }

                std::tie(line_done, i) = next_element(false);
            }

            for (; col < s[0]; ++ col)
                if (col % 8 != 0) {
                    data[index] <<= 1;
                    mask[index] <<= 1;
                } else {
                    ++ index;
                    data[index] = mask[index] = 0;
                }

            done = next_line(false);
        }

        return SDL_CreateCursor(data, mask, s[0], s[1], c[0], c[1]);
    }

    namespace cursor_pixels {
        _implementation::cursor::Pixel _ = _implementation::cursor::Pixel::_;
        _implementation::cursor::Pixel X = _implementation::cursor::Pixel::X;
        _implementation::cursor::Pixel O = _implementation::cursor::Pixel::O;
        _implementation::cursor::Pixel Z = _implementation::cursor::Pixel::Z;
    }

    Cursor::Cursor() {
        this->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    }

    Cursor::Cursor(Cursor&& other) {
        this->cursor = other.cursor;
        other.has_control = false;
    }

    Cursor::Cursor(
        const std::initializer_list<std::initializer_list<Pixel>> l,
        const Vector2s c
    ) {
        auto current_line = l.begin();
        auto current_element = current_line->begin();

        this->cursor = build_cursor(
            get_size(l),
            c,
            line_walker(current_line, current_element, l),
            [&](bool first) -> std::pair<bool, Pixel> {
                if (!first)
                    ++ current_element;
                if (current_element == current_line->end())
                    return {true, Pixel::_};
                else
                    return {false, *current_element};
            }
        );
    }

    Cursor::Cursor(
        const std::initializer_list<std::string> l,
        const Vector2s c
    ) {
        this->cursor = string_list_to_cursor(l, c);
    }

    Cursor::Cursor(
        const std::string s,
        size_t w,
        const Vector2s c
    ) {
        auto current_element = s.begin();

        if (w % 8 != 0)  // fix the width to be a multiple of 8
            w = ((w >> 3) + 1) << 3;

        size_t h = std::ceil(s.size() / w);
        if (h % 8 != 0)  // fix the height to be a multiple of 8
            h = ((h >> 3) + 1) << 3;
        // Are the same restrictions valid for the height of the cursor as for the width?

        this->cursor = build_cursor(
            Vector2s {w, h},
            c,
            [&](bool first) -> bool {
                return current_element == s.end();
            },
            [&](bool first) -> std::pair<bool, Pixel> {
                if (current_element == s.end())
                    return {true, Pixel::_};
                else {
                    Pixel out = _implementation::cursor::char_to_pixel(*current_element);
                    ++ current_element;
                    return {false, out};
                }
            }
        );
    }

    Cursor::Cursor(const std::string s, const Vector2s c) {
        this->cursor = string_list_to_cursor(_implementation::cursor::split(s), c);
    }

    Cursor::Cursor(Surface& s, Vector2s c) {
        this->cursor = SDL_CreateColorCursor(s.sdl_surface, c[0], c[1]);
    }

    Cursor::Cursor(const SDL_SystemCursor c) {
        this->cursor = SDL_CreateSystemCursor(c);
    }

    Cursor::~Cursor() {
        if (this->has_control)
            SDL_FreeCursor(this->cursor);
    }

    Cursor Cursor::pointer = SDL_SYSTEM_CURSOR_ARROW;
    Cursor Cursor::i_beam = SDL_SYSTEM_CURSOR_IBEAM;
    Cursor Cursor::wait = SDL_SYSTEM_CURSOR_WAIT;
    Cursor Cursor::crosshair = SDL_SYSTEM_CURSOR_CROSSHAIR;
    Cursor Cursor::wait_and_pointer = SDL_SYSTEM_CURSOR_WAITARROW;
    Cursor Cursor::arrow_nw_se = SDL_SYSTEM_CURSOR_SIZENWSE;
    Cursor Cursor::arrow_ne_sw = SDL_SYSTEM_CURSOR_SIZENESW;
    Cursor Cursor::arrow_horizontal = SDL_SYSTEM_CURSOR_SIZEWE;
    Cursor Cursor::arrow_vertical = SDL_SYSTEM_CURSOR_SIZENS;
    Cursor Cursor::arrow_cross = SDL_SYSTEM_CURSOR_SIZEALL;
    Cursor Cursor::slashed_circle = SDL_SYSTEM_CURSOR_NO;
    Cursor Cursor::hand = SDL_SYSTEM_CURSOR_HAND;
}
