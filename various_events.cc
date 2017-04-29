#include "various_events.hh"
#include <cstdlib>


namespace SDL {
    namespace events {
        QuitEvent::QuitEvent() : BuiltinEvent() {
            this->underlying_event.quit.type = SDL_QUIT;
        }

        AudioDeviceEvent::AudioDeviceEvent() : BuiltinEvent() {
            this->underlying_event.adevice.type = SDL_AUDIODEVICEADDED;
        }

        bool AudioDeviceEvent::is_capture() const {
            return this->underlying_event.adevice.iscapture != 0;
        }

        void AudioDeviceEvent::is_capture(bool value) {
            this->underlying_event.adevice.iscapture = value? 1 : 0;
        }

        AudioDeviceRemovedEvent::AudioDeviceRemovedEvent() : AudioDeviceEvent() {
            this->underlying_event.adevice.type = SDL_AUDIODEVICEREMOVED;
        }

        WindowManagerEvent::WindowManagerEvent() : BuiltinEvent() {
            this->underlying_event.syswm.type = SDL_SYSWMEVENT;
            this->underlying_event.syswm.msg = nullptr;
        }

        /* WindowManagerEvent::WindowManagerEvent(const WindowManagerEvent& other)
        : BuiltinEvent(other.get_sdl_event()) {
            this->underlying_event.syswm.msg = new SDL_SysWMmsg(*this->underlying_event.syswm.msg);
        }

        WindowManagerEvent::WindowManagerEvent(WindowManagerEvent&& other)
        : BuiltinEvent(std::move(other.get_sdl_event())) {
            other.underlying_event = nullptr;
        }

        WindowManagerEvent::WindowManagerEvent(SDL_SysWMmsg& msg) : WindowManagerEvent() {
            this->underlying_event.syswm.msg = &msg;
        }

        WindowManagerEvent::WindowManagerEvent(SDL_SysWMmsg&& msg) : WindowManagerEvent() {
            this->underlying_event.syswm.msg = new SDL_SysWMmsg(msg);
        } */

        WindowManagerEvent::WindowManagerEvent(SDL_SysWMmsg* msg) : WindowManagerEvent() {
            this->underlying_event.syswm.msg = msg;
        }

        /* WindowManagerEvent* WindowManagerEvent::from_copy(SDL_SysWMmsg msg) {
            return new WindowManagerEvent(std::move(msg));
        } */

        /* SDL_SysWMmsg& WindowManagerEvent::message() {
            if (this->underlying_event.syswm.msg == nullptr)
                this->underlying_event.syswm.msg = new SDL_SysWMmsg();
            return *(this->underlying_event.syswm.msg);
        }

        const SDL_SysWMmsg& WindowManagerEvent::message() const {
            return *(this->underlying_event.syswm.msg);
        } */

        bool WindowManagerEvent::has_message() const {
            return this->underlying_event.syswm.msg != nullptr;
        }

        /* WindowManagerEvent::~WindowManagerEvent() {
            delete this->underlying_event.syswm.msg;
        } */

        DropEvent::DropEvent() : BuiltinEvent() {
            this->underlying_event.drop.type = SDL_DROPFILE;
            this->underlying_event.drop.file = new char('\0');
            this->natural = false;
        }

        std::string DropEvent::file() const {
            return std::string(this->underlying_event.drop.file);
        }

        void DropEvent::file(std::string& s) {
            char* cs = new char[s.size() + 1];
            std::strcpy(cs, s.c_str());
            delete this->underlying_event.drop.file;
            this->underlying_event.drop.file = cs;
        }

        DropEvent::~DropEvent() {
            delete this->underlying_event.drop.file;
        }
    }
}
