#include "joystick_event.hh"

namespace SDL {
    namespace events {
        JoystickDeviceEvent::JoystickDeviceEvent() {
            this->underlying_event.jdevice.type = SDL_JOYDEVICEADDED;
        }

        JoystickRemovedEvent::JoystickRemovedEvent() {
            this->underlying_event.jdevice.type = SDL_JOYDEVICEREMOVED;
        }

        JoystickBallEvent::JoystickBallEvent()
        : JoystickEvent(), ball(this->underlying_event.jball.ball),
          dx(this->underlying_event.jball.xrel), dy(this->underlying_event.jball.yrel) {
            this->underlying_event.jball.type = SDL_JOYBALLMOTION;
            this->ball = 0;
            this->dx = 0;
            this->dy = 0;
        }

        JoystickBallEvent::JoystickBallEvent(const SDL_Event& ev)
        : JoystickEvent(ev), ball(this->underlying_event.jball.ball),
          dx(this->underlying_event.jball.xrel), dy(this->underlying_event.jball.yrel) {
        }

        JoystickBallEvent::JoystickBallEvent(SDL_Event&& ev)
        : JoystickEvent(ev), ball(this->underlying_event.jball.ball),
          dx(this->underlying_event.jball.xrel), dy(this->underlying_event.jball.yrel) {
        }

        JoystickBallEvent::JoystickBallEvent(
            const unsigned char ball,
            const Sint16 dx,
            const Sint16 dy
        ) : JoystickBallEvent() {
            this->ball = ball;
            this->dx = dx;
            this->dy = dy;
        }

        JoystickAxisEvent::JoystickAxisEvent()
        : JoystickEvent(), axis(this->underlying_event.jaxis.axis),
          value(this->underlying_event.jaxis.value) {
            this->underlying_event.jaxis.type = SDL_JOYAXISMOTION;
            this->axis = 0;
            this->value = 0;
        }

        JoystickAxisEvent::JoystickAxisEvent(const SDL_Event& ev)
        : JoystickEvent(ev), axis(this->underlying_event.jaxis.axis),
          value(this->underlying_event.jaxis.value) {
        }

        JoystickAxisEvent::JoystickAxisEvent(SDL_Event&& ev)
        : JoystickEvent(ev), axis(this->underlying_event.jaxis.axis),
          value(this->underlying_event.jaxis.value) {
        }

        JoystickAxisEvent::JoystickAxisEvent(const unsigned char axis, const Sint16 value)
        : JoystickAxisEvent() {
            this->axis = axis;
            this->value = value;
        }

        JoystickHatEvent::JoystickHatEvent()
        : JoystickEvent(), hat(this->underlying_event.jhat.hat) {
            this->underlying_event.jhat.type = SDL_JOYHATMOTION;
            this->hat = 0;
        }

        JoystickHatEvent::JoystickHatEvent(const SDL_Event& ev)
        : JoystickEvent(ev), hat(this->underlying_event.jhat.hat) {
        }

        JoystickHatEvent::JoystickHatEvent(SDL_Event&& ev)
        : JoystickEvent(ev), hat(this->underlying_event.jhat.hat) {
        }

        JoystickHatEvent::JoystickHatEvent(
            const unsigned char hat,
            const JoystickHatMovement m
        ) : JoystickHatEvent() {
            this->hat = hat;
            this->movement(m);
        }

        JoystickHatMovement JoystickHatEvent::movement() const {
            return JoystickHatMovement(this->underlying_event.jhat.value);
        }

        void JoystickHatEvent::movement(const JoystickHatMovement m) {
            this->underlying_event.jhat.value = Uint8(m);
        }

        JoystickButtonEvent::JoystickButtonEvent()
        : JoystickEvent(), button(this->underlying_event.jbutton.button) {
            this->underlying_event.jbutton.type = SDL_JOYBUTTONDOWN;
            this->button = 0;
            this->underlying_event.jbutton.state = SDL_PRESSED;
        }

        JoystickButtonEvent::JoystickButtonEvent(const SDL_Event& ev)
        : JoystickEvent(ev), button(this->underlying_event.jbutton.button) {
        }

        JoystickButtonEvent::JoystickButtonEvent(SDL_Event&& ev)
        : JoystickEvent(ev), button(this->underlying_event.jbutton.button) {
        }

        JoystickButtonEvent::JoystickButtonEvent(const unsigned char button)
        : JoystickButtonEvent() {
            this->button = button;
        }

        JoystickButtonUpEvent::JoystickButtonUpEvent() : JoystickButtonEvent() {
            this->underlying_event.jbutton.type = SDL_JOYBUTTONUP;
            this->underlying_event.jbutton.state = SDL_RELEASED;
        }
    }
}
