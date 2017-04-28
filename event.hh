#ifndef OBJSDL_EVENT_HH
#define OBJSDL_EVENT_HH

#include <exception>
#include <boost/exception/all.hpp>
#include <boost/any.hpp>
#include <boost/variant.hpp>
#include <typeinfo>
#include <SDL.h>
#include <chrono>

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

        SDL_Event& get();
        const SDL_Event& get() const;

        std::chrono::system_clock::time_point timestamp() const;
        Window& window() const;
        size_t window_id() const;

        virtual bool is_user_defined() const = 0;

        void push();
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


    template <typename T, typename U=VoidType>
    class UserEvent : public Event {
        protected:
        T& data;
        U& additional_data;

        public:
        UserEvent(const T& data) {
            this->data = data;
        }

        UserEvent(T&& data) {
            this->data = data;
        }

        UserEvent(const T& data, const U& additional_data) {
            this->data = data;
            this->additional_data = additional_data;
        }

        UserEvent(T&& data, const U& additional_data) {
            this->data = data;
            this->additional_data = additional_data;
        }

        UserEvent(const T& data, U&& additional_data) {
            this->data = data;
            this->additional_data = additional_data;
        }

        UserEvent(T&& data, U&& additional_data) {
            this->data = data;
            this->additional_data = additional_data;
        }

        UserEvent(const SDL_Event& ev) {
            if (ev.user.data1 != nullptr)
                this->data = *((T*) ev.user.data1);
            if (typeid(U) != typeid(VoidType) && ev.user.data2 != nullptr)
                this->additional_data = *((T*) ev.user.data2);
        }
        
        bool is_user_defined() const {
            return true;
        }
    };

    
    class BuiltinEvent : public Event {
        bool is_user_defined() const;
    };
}

// includes to special event types; they follow here to guarantee that the BuiltinEvent type is existent.

#endif
