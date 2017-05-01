#ifndef OBJSDL_MOUSE_EVENT_HH
#define OBJSDL_MOUSE_EVENT_HH

#include "event.hh"

namespace SDL {
    namespace events {
        class MouseEvent : public BuiltinEvent {
            using BuiltinEvent::BuiltinEvent;
            
            public:
            virtual bool is_touch() const = 0;
        };

        enum class MouseButton {
            left = SDL_BUTTON_LEFT,
            middle = SDL_BUTTON_MIDDLE,
            right = SDL_BUTTON_RIGHT,
            extra1 = SDL_BUTTON_X1,
            extra2 = SDL_BUTTON_X2
        };

        class MouseMotionEvent : public MouseEvent {
            public:
            Sint32& x;
            Sint32& y;
            Sint32& dx;
            Sint32& dy;

            MouseMotionEvent();
            MouseMotionEvent(const SDL_Event& ev);
            MouseMotionEvent(SDL_Event&& ev);
            MouseMotionEvent(
                const ssize_t x,
                const ssize_t y,
                const ssize_t dx,
                const ssize_t dy
            ); // TODO: which
            
            bool pressed(const MouseButton) const;
            void pressed(const MouseButton, bool);

            // TODO: which
            
            virtual bool is_touch() const;
        };

        class ClickEvent : public MouseEvent {
            public:
            Uint8& clicks;
            Sint32& x;
            Sint32& y;

            ClickEvent();
            ClickEvent(const SDL_Event& ev);
            ClickEvent(SDL_Event&& ev);
            ClickEvent(
                const ssize_t x,
                const ssize_t y,
                const MouseButton btn,
                const unsigned char clicks
            );
            ClickEvent(const ssize_t x, const ssize_t y, const MouseButton btn);

            MouseButton button() const;
            void button(const MouseButton);

            virtual bool is_touch() const;
        };

        class ClickBeginEvent : public ClickEvent {
            using ClickEvent::ClickEvent;
        };

        class ClickEndEvent : public ClickEvent {
            using ClickEvent::ClickEvent;

            public:
            ClickEndEvent();
            ClickEndEvent(
                const ssize_t x,
                const ssize_t y,
                const MouseButton btn,
                const unsigned char clicks
            );
            ClickEndEvent(const ssize_t x, const ssize_t y, const MouseButton btn);
        };

        class LeftClickEvent : public ClickEvent {
            public:
            using ClickEvent::ClickEvent;

            LeftClickEvent(
                const ssize_t x,
                const ssize_t y,
                const MouseButton btn, 
                const unsigned char clicks
            ) = delete;
            LeftClickEvent(const ssize_t x, const ssize_t y, const unsigned char clicks);
            LeftClickEvent(const ssize_t x, const ssize_t y);
        };

        class LeftClickBeginEvent : public LeftClickEvent, public ClickBeginEvent {
            using LeftClickEvent::LeftClickEvent;
        };

        class LeftClickEndEvent : public LeftClickEvent, public ClickEndEvent {
            using LeftClickEvent::LeftClickEvent;
        };

        class MiddleClickEvent : public ClickEvent {
            public:
            using ClickEvent::ClickEvent;

            MiddleClickEvent();
            MiddleClickEvent(
                const ssize_t x,
                const ssize_t y,
                const MouseButton btn, 
                const unsigned char clicks
            ) = delete;
            MiddleClickEvent(const ssize_t x, const ssize_t y, const unsigned char clicks);
            MiddleClickEvent(const ssize_t x, const ssize_t y);
        };

        class MiddleClickBeginEvent : public MiddleClickEvent, public ClickBeginEvent {
            using MiddleClickEvent::MiddleClickEvent;
        };

        class MiddleClickEndEvent : public MiddleClickEvent, public ClickEndEvent {
            using MiddleClickEvent::MiddleClickEvent;
        };

        class RightClickEvent : public ClickEvent {
            public:
            using ClickEvent::ClickEvent;

            RightClickEvent();
            RightClickEvent(
                const ssize_t x,
                const ssize_t y,
                const MouseButton btn, 
                const unsigned char clicks
            ) = delete;
            RightClickEvent(const ssize_t x, const ssize_t y, const unsigned char clicks);
            RightClickEvent(const ssize_t x, const ssize_t y);
        };

        class RightClickBeginEvent : public RightClickEvent, public ClickBeginEvent {
            using RightClickEvent::RightClickEvent;
        };

        class RightClickEndEvent : public RightClickEvent, public ClickEndEvent {
            using RightClickEvent::RightClickEvent;
        };

        class Extra1ClickEvent : public ClickEvent {
            public:
            using ClickEvent::ClickEvent;

            Extra1ClickEvent();
            Extra1ClickEvent(
                const ssize_t x,
                const ssize_t y,
                const MouseButton btn, 
                const unsigned char clicks
            ) = delete;
            Extra1ClickEvent(const ssize_t x, const ssize_t y, const unsigned char clicks);
            Extra1ClickEvent(const ssize_t x, const ssize_t y);
        };

        class Extra1ClickBeginEvent : public Extra1ClickEvent, public ClickBeginEvent {
            using Extra1ClickEvent::Extra1ClickEvent;
        };

        class Extra1ClickEndEvent : public Extra1ClickEvent, public ClickEndEvent {
            using Extra1ClickEvent::Extra1ClickEvent;
        };

        class Extra2ClickEvent : public ClickEvent {
            public:
            using ClickEvent::ClickEvent;

            Extra2ClickEvent();
            Extra2ClickEvent(
                const ssize_t x,
                const ssize_t y,
                const MouseButton btn, 
                const unsigned char clicks
            ) = delete;
            Extra2ClickEvent(const ssize_t x, const ssize_t y, const unsigned char clicks);
            Extra2ClickEvent(const ssize_t x, const ssize_t y);
        };

        class Extra2ClickBeginEvent : public Extra2ClickEvent, public ClickBeginEvent {
            using Extra2ClickEvent::Extra2ClickEvent;
        };

        class Extra2ClickEndEvent : public Extra2ClickEvent, public ClickEndEvent {
            using Extra2ClickEvent::Extra2ClickEvent;
        };

        class ScrollEvent : public MouseEvent {
            public:
            Sint32& dx;
            Sint32& dy;

            ScrollEvent();
            ScrollEvent(const SDL_Event& ev);
            ScrollEvent(SDL_Event&& ev);
            ScrollEvent(ssize_t dx, ssize_t dy);

            virtual bool is_touch() const;
        };
    }
}

#endif
