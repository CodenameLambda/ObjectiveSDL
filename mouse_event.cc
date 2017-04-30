#include "mouse_event.hh"

namespace SDL {
    namespace events {
        MouseMotionEvent::MouseMotionEvent()
        : MouseEvent::MouseEvent(), x(this->underlying_event.motion.x),
          y(this->underlying_event.motion.y), dx(this->underlying_event.motion.xrel),
          dy(this->underlying_event.motion.yrel) {
            this->underlying_event.motion.type = SDL_MOUSEMOTION;
            int x;
            int y;
            SDL_GetMouseState(&x, &y);
            this->x = x;
            this->y = y;
            this->dx = 0;
            this->dy = 0;
        }

        MouseMotionEvent::MouseMotionEvent(const SDL_Event& ev)
        : MouseEvent::MouseEvent(ev), x(this->underlying_event.motion.x),
          y(this->underlying_event.motion.y), dx(this->underlying_event.motion.xrel),
          dy(this->underlying_event.motion.yrel) {
        }

        MouseMotionEvent::MouseMotionEvent(SDL_Event&& ev)
        : MouseEvent::MouseEvent(ev), x(this->underlying_event.motion.x),
          y(this->underlying_event.motion.y), dx(this->underlying_event.motion.xrel),
          dy(this->underlying_event.motion.yrel) {
        }

        MouseMotionEvent::MouseMotionEvent(
                const ssize_t x,
                const ssize_t y,
                const ssize_t dx,
                const ssize_t dy
        ) : MouseMotionEvent() {
            this->x = x;
            this->y = y;
            this->dx = dx;
            this->dy = dy;
        }

        bool MouseMotionEvent::pressed(const MouseButton btn) const {
            return size_t(this->underlying_event.motion.state) & size_t(SDL_BUTTON(size_t(btn)));
        }

        void MouseMotionEvent::pressed(const MouseButton btn, bool value) {
            if (value != this->pressed(btn))
                this->underlying_event.motion.state = (
                    size_t(this->underlying_event.motion.state) ^ size_t(SDL_BUTTON(size_t(btn)))
                );
        }

        bool MouseMotionEvent::is_touch() const {
            return this->underlying_event.motion.which != SDL_TOUCH_MOUSEID;
        }

        ClickEvent::ClickEvent()
        : MouseEvent(), x(this->underlying_event.button.x), y(this->underlying_event.button.y),
          clicks(this->underlying_event.button.clicks) {
              this->underlying_event.button.type = SDL_MOUSEBUTTONDOWN;
              this->button(MouseButton::left);
              this->underlying_event.button.state = SDL_PRESSED;
              this->underlying_event.button.clicks = 1;
              int x;
              int y;
              SDL_GetMouseState(&x, &y);
              this->underlying_event.button.x = x;
              this->underlying_event.button.y = y;
        }

        ClickEvent::ClickEvent(const SDL_Event& ev)
        : MouseEvent(ev), x(this->underlying_event.button.x), y(this->underlying_event.button.y),
          clicks(this->underlying_event.button.clicks) {
        }

        ClickEvent::ClickEvent(SDL_Event&& ev)
        : MouseEvent(ev), x(this->underlying_event.button.x), y(this->underlying_event.button.y),
          clicks(this->underlying_event.button.clicks) {
        }

        ClickEvent::ClickEvent(
            const ssize_t x,
            const ssize_t y,
            const MouseButton btn,
            const unsigned char clicks=1
        ) : ClickEvent() {
            this->x = x;
            this->y = y;
            this->button(btn);
            this->clicks = clicks;
        }

        MouseButton ClickEvent::button() const {
            return MouseButton(this->underlying_event.button.button);
        }

        void ClickEvent::button(const MouseButton btn) {
            this->underlying_event.button.button = size_t(btn);
        }

        bool ClickEvent::is_touch() const {
            return this->underlying_event.button.which != SDL_TOUCH_MOUSEID;
        }

        ClickEndEvent::ClickEndEvent() : ClickEvent() {
            this->underlying_event.button.type = SDL_MOUSEBUTTONUP;
            this->underlying_event.button.state = SDL_RELEASED;
        }

        ClickEndEvent::ClickEndEvent(
            const ssize_t x,
            const ssize_t y,
            const MouseButton btn,
            const unsigned char clicks=1
        ) : ClickEvent(x, y, btn, clicks) {
            this->underlying_event.button.type = SDL_MOUSEBUTTONUP;
            this->underlying_event.button.state = SDL_RELEASED;
        }

        LeftClickEvent::LeftClickEvent(
            const ssize_t x,
            const ssize_t y,
            const unsigned char clicks=1
        ) : ClickEvent(x, y, MouseButton::left, clicks) {
        }

        MiddleClickEvent::MiddleClickEvent() : ClickEvent() {
            this->button(MouseButton::middle);
        }

        MiddleClickEvent::MiddleClickEvent(
            const ssize_t x,
            const ssize_t y,
            const unsigned char clicks=1
        ) : ClickEvent(x, y, MouseButton::middle, clicks) {
        }

        RightClickEvent::RightClickEvent() : ClickEvent() {
            this->button(MouseButton::right);
        }

        RightClickEvent::RightClickEvent(
            const ssize_t x,
            const ssize_t y,
            const unsigned char clicks=1
        ) : ClickEvent(x, y, MouseButton::right, clicks) {
        }

        Extra1ClickEvent::Extra1ClickEvent() : ClickEvent() {
            this->button(MouseButton::extra1);
        }

        Extra1ClickEvent::Extra1ClickEvent(
            const ssize_t x,
            const ssize_t y,
            const unsigned char clicks=1
        ) : ClickEvent(x, y, MouseButton::extra1, clicks) {
        }

        Extra2ClickEvent::Extra2ClickEvent() : ClickEvent() {
            this->button(MouseButton::extra2);
        }

        Extra2ClickEvent::Extra2ClickEvent(
            const ssize_t x,
            const ssize_t y,
            const unsigned char clicks=1
        ) : ClickEvent(x, y, MouseButton::extra2, clicks) {
        }

        ScrollEvent::ScrollEvent()
        : MouseEvent(), dx(this->underlying_event.wheel.x), dy(this->underlying_event.wheel.y) {
            this->underlying_event.wheel.type = SDL_MOUSEWHEEL;
            this->dx = 0;
            this->dy = 0;
        }

        ScrollEvent::ScrollEvent(const SDL_Event& ev)
        : MouseEvent(ev), dx(this->underlying_event.wheel.x), dy(this->underlying_event.wheel.y) {
            if (this->underlying_event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED) {
                this->dx = - this->dx;
                this->dy = - this->dy;
            }
        }

        ScrollEvent::ScrollEvent(SDL_Event&& ev)
        : MouseEvent(ev), dx(this->underlying_event.wheel.x), dy(this->underlying_event.wheel.y) {
            if (this->underlying_event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED) {
                this->dx = - this->dx;
                this->dy = - this->dy;
            }
        }

        ScrollEvent::ScrollEvent(ssize_t dx, ssize_t dy) : ScrollEvent() {
            this->dx = dx;
            this->dy = dy;
        }

        bool ScrollEvent::is_touch() const {
            return this->underlying_event.wheel.which != SDL_TOUCH_MOUSEID;
        }
    }
}
