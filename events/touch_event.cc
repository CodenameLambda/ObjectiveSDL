#include "touch_event.hh"


namespace SDL {
    namespace events {
        bool TouchEvent::is_touch() const {
            return true;
        }

        FingerEvent::FingerEvent()
        : TouchEvent(), x(this->underlying_event.tfinger.x), y(this->underlying_event.tfinger.y),
          dx(this->underlying_event.tfinger.dx), dy(this->underlying_event.tfinger.dy),
          pressure(this->underlying_event.tfinger.pressure),
          finger(this->underlying_event.tfinger.fingerId) {
            this->underlying_event.tfinger.type = SDL_FINGERDOWN;
            this->finger = 0;
            this->x = .5f;
            this->y = .5f;
            this->dx = .0f;
            this->dy = .0f;
            this->pressure = 1.f;
        }

        FingerEvent::FingerEvent(const SDL_Event& ev)
        : TouchEvent(ev), x(this->underlying_event.tfinger.x), y(this->underlying_event.tfinger.y),
          dx(this->underlying_event.tfinger.dx), dy(this->underlying_event.tfinger.dy),
          pressure(this->underlying_event.tfinger.pressure),
          finger(this->underlying_event.tfinger.fingerId) {
        }

        FingerEvent::FingerEvent(SDL_Event&& ev)
        : TouchEvent(ev), x(this->underlying_event.tfinger.x), y(this->underlying_event.tfinger.y),
          dx(this->underlying_event.tfinger.dx), dy(this->underlying_event.tfinger.dy),
          pressure(this->underlying_event.tfinger.pressure),
          finger(this->underlying_event.tfinger.fingerId) {
        }

        FingerEvent::FingerEvent(
            const SDL_FingerID finger,
            const float x,
            const float y,
            const float dx,
            const float dy,
            const float pressure
        ) : FingerEvent() {
            this->finger = finger;
            this->x = x;
            this->y = y;
            this->dx = dx;
            this->dy = dy;
        }

        FingerMotionEvent::FingerMotionEvent() {
            this->underlying_event.tfinger.type = SDL_FINGERMOTION;
        }

        FingerMotionEvent::FingerMotionEvent(
            const SDL_FingerID finger,
            const float x,
            const float y,
            const float dx,
            const float dy,
            const float pressure
        ) : FingerEvent(finger, x, y, dx, dy, pressure) {
            this->underlying_event.tfinger.type = SDL_FINGERMOTION;
        }

        FingerDownEvent::FingerDownEvent(
            const SDL_FingerID finger,
            const float x,
            const float y,
            const float pressure
        ) : FingerEvent(finger, x, y, .0f, .0f, pressure) {
        }

        FingerUpEvent::FingerUpEvent() : FingerEvent() {
            this->underlying_event.tfinger.type = SDL_FINGERUP;
        }

        FingerUpEvent::FingerUpEvent(
            const SDL_FingerID finger,
            const float x,
            const float y,
            const float pressure
        ) : FingerEvent(finger, x, y, .0f, .0f, pressure) {
            this->underlying_event.tfinger.type = SDL_FINGERUP;
        }

        MultiGestureEvent::MultiGestureEvent()
        : TouchEvent(), x(this->underlying_event.mgesture.x), y(this->underlying_event.mgesture.y),
          rotation(this->underlying_event.mgesture.dTheta),
          distance(this->underlying_event.mgesture.dDist),
          finger_count(this->underlying_event.mgesture.numFingers) {
            this->underlying_event.mgesture.type = SDL_MULTIGESTURE;
            this->x = .5f;
            this->y = .5f;
            this->rotation = .0f;
            this->distance = .25f;
            this->finger_count = 2;
        }

        MultiGestureEvent::MultiGestureEvent(const SDL_Event& ev)
        : TouchEvent(ev), x(this->underlying_event.mgesture.x), y(this->underlying_event.mgesture.y),
          rotation(this->underlying_event.mgesture.dTheta),
          distance(this->underlying_event.mgesture.dDist),
          finger_count(this->underlying_event.mgesture.numFingers) {
        }

        MultiGestureEvent::MultiGestureEvent(SDL_Event&& ev)
        : TouchEvent(ev), x(this->underlying_event.mgesture.x), y(this->underlying_event.mgesture.y),
          rotation(this->underlying_event.mgesture.dTheta),
          distance(this->underlying_event.mgesture.dDist),
          finger_count(this->underlying_event.mgesture.numFingers) {
        }

        MultiGestureEvent::MultiGestureEvent(
            const float x,
            const float y,
            const float rotation,
            const float distance,
            const size_t finger_count
        ) : MultiGestureEvent() {
            this->x = x;
            this->y = y;
            this->rotation = rotation;
            this->distance = distance;
            this->finger_count = finger_count;
        }

        GestureEvent::GestureEvent()
        : TouchEvent(), gesture(this->underlying_event.dgesture.gestureId),
          x(this->underlying_event.dgesture.x), y(this->underlying_event.dgesture.y),
          error(this->underlying_event.dgesture.error) {
            this->underlying_event.dgesture.type = SDL_DOLLARGESTURE;
            this->gesture = 0;
            this->error = .5f;
            this->x = .5f;
            this->y = .5f;
        }

        GestureEvent::GestureEvent(const SDL_Event& ev)
        : TouchEvent(ev), gesture(this->underlying_event.dgesture.gestureId),
          x(this->underlying_event.dgesture.x), y(this->underlying_event.dgesture.y),
          error(this->underlying_event.dgesture.error) {
        }

        GestureEvent::GestureEvent(SDL_Event&& ev)
        : TouchEvent(ev), gesture(this->underlying_event.dgesture.gestureId),
          x(this->underlying_event.dgesture.x), y(this->underlying_event.dgesture.y),
          error(this->underlying_event.dgesture.error) {
        }

        GestureEvent::GestureEvent(
            const SDL_GestureID gesture,
            const float x,
            const float y,
            const float error
        ) : GestureEvent() {
            this->gesture = gesture;
            this->x = x;
            this->y = y;
            this->error = error;
        }

        GestureRecordedEvent::GestureRecordedEvent() : GestureEvent() {
            this->underlying_event.dgesture.type = SDL_DOLLARRECORD;
        }

        GestureRecordedEvent::GestureRecordedEvent(
            const SDL_GestureID gesture,
            const float x,
            const float y,
            const float error
        ) : GestureEvent(gesture, x, y, error) {
            this->underlying_event.dgesture.type = SDL_DOLLARRECORD;
        }
    }
}
