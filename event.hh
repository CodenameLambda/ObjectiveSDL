#ifndef OBJSDL_EVENT_HH
#define OBJSDL_EVENT_HH

#include <exception>
#include <boost/exception/all.hpp>
#include <boost/any.hpp>
#include <boost/variant.hpp>
#include <typeinfo>
#include <SDL.h>
#include <chrono>
#include <unordered_map>
#include <functional>

struct Window {  // TODO: Remove in favour of the real class
};

namespace SDL {
    class Event;


    namespace _implementation {
        namespace event {
            template <typename Variant, typename T, typename... V>
            Variant get_variant(const Event& ev);
        }
    }


    class OtherEventType : public boost::exception, public std::exception {
        const char* what() const noexcept;
    };
    

    struct VoidType {
    };


    class Event {
        protected:
        SDL_Event underlying_event;

        public:
        Event();
        Event(const SDL_Event& ev);
        Event(SDL_Event&& ev);

        template <typename T>
        T* get() {
            T* casted = dynamic_cast<T*>(*this);
            if (casted == nullptr)
                throw OtherEventType{};
            return casted;
        }

        template <typename... V>
        boost::variant<V...> get_variant() {
            return _implementation::event::get_variant<boost::variant<V...>, V...>(*this);
        }

        template <typename T>
        const T* get() const {
            const T* casted = dynamic_cast<T*>(*this);
            if (casted == nullptr)
                throw OtherEventType{};
            return casted;
        }

        template <typename T>
        bool holds() const {
            return dynamic_cast<T*>(*this) != nullptr;
        }

        SDL_Event& get_sdl_event();
        const SDL_Event& get_sdl_event() const;

        std::chrono::system_clock::time_point timestamp() const;
        Window& window() const;
        size_t window_id() const;

        virtual bool is_user_defined() const = 0;

        void push();

        virtual ~Event();
    };

    
    namespace _implementation {
        namespace event {
            template <typename Variant, typename T, typename U, typename... V>
            Variant get_variant(const Event& ev) {
                try {
                    return Variant(ev.get<T>());
                } catch (OtherEventType) {
                    return get_variant<Variant, U, V...>(ev);
                }
            }

            template <typename Variant, typename T>
            Variant get_variant(const Event& ev) {
                return Variant(ev.get<T>());  // can throw
            }
        }
    }


    template <typename T=VoidType, typename U=VoidType>
    class UserEvent : public Event {
        protected:
        T& data;
        U& additional_data;

        public:
        UserEvent()
        : Event(), data(this->underlying_event.user.data1),
          additional_data(this->underlying_event.user.data2) {
        }

        UserEvent(const UserEvent<T, U>& other) : UserEvent() {
            this->data = other.data;
        }

        UserEvent(const T& data) : UserEvent() {
            this->data = data;
        }

        UserEvent(T&& data) : UserEvent() {
            this->data = data;
        }

        UserEvent(const T& data, const U& additional_data) : UserEvent() {
            this->data = data;
            this->additional_data = additional_data;
        }

        UserEvent(T&& data, const U& additional_data) : UserEvent() {
            this->data = data;
            this->additional_data = additional_data;
        }

        UserEvent(const T& data, U&& additional_data) : UserEvent() {
            this->data = data;
            this->additional_data = additional_data;
        }

        UserEvent(T&& data, U&& additional_data) : UserEvent() {
            this->data = data;
            this->additional_data = additional_data;
        }

        UserEvent(const SDL_Event& ev)
        : Event(ev), data(this->underlying_event.user.data1),
          additional_data(this->underlying_event.user.data2) {
            if (typeid(U) != typeid(VoidType) && ev.user.data1 != nullptr)
                this->data = *((T*) ev.user.data1);
            if (typeid(U) != typeid(VoidType) && ev.user.data2 != nullptr)
                this->additional_data = *((T*) ev.user.data2);
        }
        
        virtual bool is_user_defined() const {
            return true;
        }

        virtual ~UserEvent() {
            if (typeid(T) != typeid(VoidType))
                delete &this->data;
            if (typeid(U) != typeid(VoidType))
                delete &this->additional_data;
        }
    };

    
    class BuiltinEvent : public Event {
        using Event::Event;

        virtual bool is_user_defined() const;
    };


    extern const std::unordered_map<size_t, std::function<Event*(SDL_Event)>> event_types;
    extern std::unordered_map<size_t, std::function<Event*(SDL_Event)>> user_types;


    template <typename T>
    size_t register_user_event(
            std::function<Event*(SDL_Event)> f = [](SDL_Event ev){ return new T(ev); }
    ) {
        for (size_t id = 0; true; ++id)
            if (user_types.find(id) == user_types.end())
                user_types[id] = f;
    }
}

// includes to special event types; they follow here to guarantee that the BuiltinEvent type is existent.
#include "window_event.hh"
#include "keyboard_event.hh"

#endif
