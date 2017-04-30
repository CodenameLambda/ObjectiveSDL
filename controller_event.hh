#ifndef OBJSDL_CONTROLLER_EVENT_HH
#define OBJSDL_CONTROLLER_EVENT_HH

#include "event.hh"

namespace SDL {
    namespace events {
        class ControllerEvent : public BuiltinEvent {
            using BuiltinEvent::BuiltinEvent;
        };

        class ControllerDeviceEvent : public ControllerEvent {
            using ControllerEvent::ControllerEvent;

            public:
            ControllerDeviceEvent();
        };

        class ControllerAddedEvent : public ControllerDeviceEvent {
            using ControllerDeviceEvent::ControllerDeviceEvent;
        };

        class ControllerRemovedEvent : public ControllerDeviceEvent {
            using ControllerDeviceEvent::ControllerDeviceEvent;

            public:
            ControllerRemovedEvent();
        };

        class ControllerRemappedEvent : public ControllerDeviceEvent {
            using ControllerDeviceEvent::ControllerDeviceEvent;

            public:
            ControllerRemappedEvent();
        };

        class ControllerAxisEvent : public ControllerEvent {
            public:
            Uint8& axis;
            Sint16& value;

            ControllerAxisEvent();
            ControllerAxisEvent(const SDL_Event& ev);
            ControllerAxisEvent(SDL_Event&& ev);
            ControllerAxisEvent(const unsigned char axis, const ssize_t value);
        };

        class ControllerButtonEvent : public ControllerEvent {
            public:
            Uint8& button;

            ControllerButtonEvent();
            ControllerButtonEvent(const SDL_Event& ev);
            ControllerButtonEvent(SDL_Event&& ev);
            ControllerButtonEvent(const unsigned char button);
        };

        class ControllerButtonDownEvent : public ControllerButtonEvent {
            using ControllerButtonEvent::ControllerButtonEvent;
        };

        class ControllerButtonUpEvent : public ControllerButtonEvent {
            using ControllerButtonEvent::ControllerButtonEvent;

            public:
            ControllerButtonUpEvent();
            ControllerButtonUpEvent(const unsigned char button);
        };
    }
}

#endif
