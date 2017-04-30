#ifndef OBJSDL_TOUCH_EVENT_HH
#define OBJSDL_TOUCH_EVENT_HH

#include "mouse_event.hh"

namespace SDL {
    namespace events {
        class TouchEvent : public MouseEvent {
            using MouseEvent::MouseEvent;

            virtual bool is_touch() const;
        };

        class FingerEvent : public TouchEvent {
            public:
            float& x;
            float& y;
            float& dx;
            float& dy;
            float& pressure;
            SDL_FingerID& finger;

            FingerEvent();
            FingerEvent(const SDL_Event&);
            FingerEvent(SDL_Event&&);
            FingerEvent(
                const SDL_FingerID finger,
                const float x,
                const float y,
                const float dx,
                const float dy,
                const float pressure=1.f
            );
        };

        class FingerMotionEvent : public FingerEvent {
            using FingerEvent::FingerEvent;

            public:
            FingerMotionEvent();
            FingerMotionEvent(
                const SDL_FingerID finger,
                const float x,
                const float y,
                const float dx,
                const float dy,
                const float pressure=1.f
            );
        };

        class FingerDownEvent : public FingerEvent {
            using FingerEvent::FingerEvent;

            public:
            FingerDownEvent(
                const SDL_FingerID finger,
                const float x,
                const float y,
                const float pressure=1.f
            );
        };

        class FingerUpEvent : public FingerEvent {
            using FingerEvent::FingerEvent;

            public:
            FingerUpEvent();
            FingerUpEvent(
                const SDL_FingerID finger,
                const float x,
                const float y,
                const float dx,
                const float dy,
                const float pressure=1.f
            );
            FingerUpEvent(
                const SDL_FingerID finger,
                const float x,
                const float y,
                const float pressure=1.f
            );
        };

        class MultiGestureEvent : public TouchEvent {
            public:
            float& x;
            float& y;
            float& rotation;
            float& distance;
            Uint16& finger_count;
            
            MultiGestureEvent();
            MultiGestureEvent(const SDL_Event&);
            MultiGestureEvent(SDL_Event&&);
            MultiGestureEvent(
                const float x,
                const float y,
                const float rotation,
                const float distance,
                const size_t finger_count
            );
        };

        class GestureEvent : public TouchEvent {
            public:
            SDL_GestureID& gesture;
            float& error;
            float& x;
            float& y;

            GestureEvent();
            GestureEvent(const SDL_Event&);
            GestureEvent(SDL_Event&&);
            GestureEvent(
                const SDL_GestureID gesture,
                const float x,
                const float y,
                const float error=.0f
            );
        };

        class GestureRecognizedEvent : public GestureEvent {
            using GestureEvent::GestureEvent;
        };

        class GestureRecordedEvent : public GestureEvent {
            using GestureEvent::GestureEvent;

            public:
            GestureRecordedEvent();
            GestureRecordedEvent(
                const SDL_GestureID gesture,
                const float x,
                const float y,
                const float error=.0f
            );
        };
    }
}

#endif
