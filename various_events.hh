#ifndef OBJSDL_VARIOUS_EVENTS_HH
#define OBJSDL_VARIOUS_EVENTS_HH
#include "event.hh"


namespace SDL {
    namespace events {
        class QuitEvent : public BuiltinEvent {
            using BuiltinEvent::BuiltinEvent;

            public:
            QuitEvent();
        };

        class AudioDeviceEvent : public BuiltinEvent {
            using BuiltinEvent::BuiltinEvent;

            public:
            AudioDeviceEvent();

            // TODO Constructor(AudioDevice, added, capture=)
            // TODO Return audio device with "device()"
            
            bool is_capture() const;
            void is_capture(bool);
        };

        class AudioDeviceAddedEvent : public AudioDeviceEvent {
            using AudioDeviceEvent::AudioDeviceEvent;
        };

        class AudioDeviceRemovedEvent : public AudioDeviceEvent {
            using AudioDeviceEvent::AudioDeviceEvent;

            public:
            AudioDeviceRemovedEvent();
        };

        class WindowManagerEvent : public BuiltinEvent {
            using BuiltinEvent::BuiltinEvent;

            public:
            WindowManagerEvent();
            // WindowManagerEvent(const WindowManagerEvent& other);
            WindowManagerEvent(const WindowManagerEvent& other) = delete;
            WindowManagerEvent(WindowManagerEvent&& other);
            // WindowManagerEvent(SDL_SysWMmsg& msg);
            // WindowManagerEvent(SDL_SysWMmsg&& msg);
            WindowManagerEvent(SDL_SysWMmsg* msg);

            // static WindowManagerEvent* from_copy(SDL_SysWMmsg msg);

            // SDL_SysWMmsg& message();
            // const SDL_SysWMmsg& message() const;

            bool has_message() const;

            // virtual ~WindowManagerEvent();
        };

        class DropEvent : public BuiltinEvent {
            using BuiltinEvent::BuiltinEvent;
            bool natural = true;

            public:
            DropEvent();

            std::string file() const;
            void file(std::string&);

            virtual ~DropEvent();
        };
    }
}
#endif
