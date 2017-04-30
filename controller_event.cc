#include "controller_event.hh"


namespace SDL {
    namespace events {
        ControllerDeviceEvent::ControllerDeviceEvent() {
            this->underlying_event.cdevice.type = SDL_CONTROLLERDEVICEADDED;
        }

        ControllerRemovedEvent::ControllerRemovedEvent() {
            this->underlying_event.cdevice.type = SDL_CONTROLLERDEVICEREMOVED;
        }

        ControllerRemappedEvent::ControllerRemappedEvent() {
            this->underlying_event.cdevice.type = SDL_CONTROLLERDEVICEREMAPPED;
        }

        ControllerAxisEvent::ControllerAxisEvent()
        : ControllerEvent(), axis(this->underlying_event.caxis.axis),
          value(this->underlying_event.caxis.value) {
            this->underlying_event.caxis.type = SDL_CONTROLLERAXISMOTION;
            this->axis = 0;
            this->value = 0;
        }

        ControllerAxisEvent::ControllerAxisEvent(const SDL_Event& ev)
        : ControllerEvent(ev), axis(this->underlying_event.caxis.axis),
          value(this->underlying_event.caxis.value) {
        }

        ControllerAxisEvent::ControllerAxisEvent(SDL_Event&& ev)
        : ControllerEvent(ev), axis(this->underlying_event.caxis.axis),
          value(this->underlying_event.caxis.value) {
        }

        ControllerAxisEvent::ControllerAxisEvent(const unsigned char axis, const ssize_t value)
        : ControllerAxisEvent() {
            this->axis = axis;
            this->value = value;
        }

        ControllerButtonEvent::ControllerButtonEvent()
        : ControllerEvent(), button(this->underlying_event.cbutton.button) {
            this->underlying_event.cbutton.type = SDL_CONTROLLERBUTTONDOWN;
            this->button = 0;
            this->underlying_event.cbutton.state = SDL_PRESSED;
        }

        ControllerButtonEvent::ControllerButtonEvent(const SDL_Event& ev)
        : ControllerEvent(ev), button(this->underlying_event.cbutton.button) {
        }

        ControllerButtonEvent::ControllerButtonEvent(SDL_Event&& ev)
        : ControllerEvent(ev), button(this->underlying_event.cbutton.button) {
        }

        ControllerButtonEvent::ControllerButtonEvent(const unsigned char button)
        : ControllerButtonEvent() {
            this->button = button;
        }

        ControllerButtonUpEvent::ControllerButtonUpEvent() : ControllerButtonEvent() {
            this->underlying_event.cbutton.type = SDL_CONTROLLERBUTTONUP;
            this->underlying_event.cbutton.state = SDL_RELEASED;
        }

        ControllerButtonUpEvent::ControllerButtonUpEvent(const unsigned char button)
        : ControllerButtonEvent() {
            this->underlying_event.cbutton.type = SDL_CONTROLLERBUTTONUP;
            this->underlying_event.cbutton.state = SDL_RELEASED;
        }
    }
}
