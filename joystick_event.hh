#ifndef OBJSDL_JOYSTICK_EVENT_HH
#define OBJSDL_JOYSTICK_EVENT_HH

#include "event.hh"


namespace SDL {
    namespace events {
        class JoystickEvent : public BuiltinEvent {
            using BuiltinEvent::BuiltinEvent;
        };

        class JoystickDeviceEvent : public JoystickEvent {
            using JoystickEvent::JoystickEvent;

            public:
            JoystickDeviceEvent();

            // TODO
        };

        class JoystickAddedEvent : public JoystickDeviceEvent {
            using JoystickDeviceEvent::JoystickDeviceEvent;
        };

        class JoystickRemovedEvent : public JoystickDeviceEvent {
            using JoystickDeviceEvent::JoystickDeviceEvent;

            public:
            JoystickRemovedEvent();
        };

        class JoystickBallEvent : public JoystickEvent {
            public:
            Uint8& ball;
            Sint16& dx;
            Sint16& dy;

            JoystickBallEvent();
            JoystickBallEvent(const SDL_Event& ev);
            JoystickBallEvent(SDL_Event&& ev);
            JoystickBallEvent(
                const unsigned char ball,
                const Sint16 dx,
                const Sint16 dy
            );
        };

        class JoystickAxisEvent : public JoystickEvent {
            public:
            Uint8& axis;
            Sint16& value;

            JoystickAxisEvent();
            JoystickAxisEvent(const SDL_Event& ev);
            JoystickAxisEvent(SDL_Event&& ev);
            JoystickAxisEvent(const unsigned char axis, const Sint16 value);
        };

        enum class JoystickHatMovement {
            left_up = SDL_HAT_LEFTUP,
            up = SDL_HAT_UP,
            right_up = SDL_HAT_RIGHTUP,
            left = SDL_HAT_LEFT,
            centered = SDL_HAT_CENTERED,
            right = SDL_HAT_RIGHT,
            left_down = SDL_HAT_LEFTDOWN,
            down = SDL_HAT_DOWN,
            right_down = SDL_HAT_RIGHTDOWN
        };

        class JoystickHatEvent : public JoystickEvent {
            public:
            Uint8& hat;

            JoystickHatEvent();
            JoystickHatEvent(const SDL_Event& ev);
            JoystickHatEvent(SDL_Event&& ev);
            JoystickHatEvent(
                const unsigned char hat,
                const JoystickHatMovement movement
            );

            JoystickHatMovement movement() const;
            void movement(const JoystickHatMovement);
        };

        class JoystickButtonEvent : public JoystickEvent {
            public:
            Uint8& button;

            JoystickButtonEvent();
            JoystickButtonEvent(const SDL_Event& ev);
            JoystickButtonEvent(SDL_Event&& ev);
            JoystickButtonEvent(const unsigned char button);
        };

        class JoystickButtonDownEvent : public JoystickButtonEvent {
            using JoystickButtonEvent::JoystickButtonEvent;
        };

        class JoystickButtonUpEvent : public JoystickButtonEvent {
            using JoystickButtonEvent::JoystickButtonEvent;

            public:
            JoystickButtonUpEvent();
            JoystickButtonUpEvent(const unsigned char button);
        };
    }
}

#endif
