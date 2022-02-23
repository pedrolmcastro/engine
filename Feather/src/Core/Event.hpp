#pragma once


#include "Precompiled.hpp"
#include "Math/Vector.hpp"
#include "Input/Mouse.hpp"
#include "Input/Key.hpp"


#define BindEvent(function) [this](auto&&... args) -> decltype(auto) { return this->function(std::forward<decltype(args)>(args)...); }

#define __EventType__(type)                                     \
    static Type GetStaticType() { return type; }                \
    Type GetType() const override { return GetStaticType(); }   \

#define __EventString__(str) operator std::string() const override { return str; }

#define __EventCategory__(category) Category GetCategory() const override { return category; }


namespace Feather {
    class Event {
    public:
        enum class Type {
            WINDOW_RESIZE, WINDOW_MOVE, WINDOW_FOCUS, WINDOW_UNFOCUS, WINDOW_HOVER, WINDOW_UNHOVER, WINDOW_CLOSE,
            MOUSE_PRESS, MOUSE_RELEASE, MOUSE_SCROLL, MOUSE_MOVE,
            KEY_PRESS, KEY_RELEASE,
        };

        enum class Category {
            WINDOW   = 1 << 0,
            INPUT    = 1 << 1,
            MOUSE    = 1 << 2,
            KEY      = 1 << 3,
        };

        class Dispatcher;

        class WindowMove;
        class WindowFocus;
        class WindowHover;
        class WindowClose;
        class WindowResize;
        class WindowUnfocus;
        class WindowUnhover;

        class MouseMove;
        class MousePress;
        class MouseScroll;
        class MouseRelease;

        class KeyPress;
        class KeyRelease;


        bool handled = false;

        virtual ~Event() = default;

        friend Category operator|(Category first, Category second) { return Category(int(first) | int(second)); }
        friend bool operator&(Category first, Category second) { return int(first) & int(second); }
        bool In(Category category) { return GetCategory() & category; }

        virtual Type GetType() const = 0;
        virtual Category GetCategory() const = 0;

        // TODO: Use operator<<()
        virtual operator std::string() const { return "Event"; }
    };


    // TODO: Event Bus
    class Event::Dispatcher {
    public:
        Dispatcher(Event& event): event(event) {}

        template<typename T, typename F> bool Dispatch(const F& callback) {
            if (event.GetType() == T::GetStaticType()) {
                event.handled |= callback((T&)event);
                return true;
            }
            return false;
        }
    private:
        Event& event;
    };


    class Event::WindowResize: public Event {
    public:
        WindowResize(const Math::Unsigned2& size): size(size) {}

        unsigned GetWidth() const { return size.x; }
        unsigned GetHeight() const { return size.y; }
        Math::Unsigned2 GetSize() const { return size; }

        operator std::string() const override {
            std::stringstream stream;
            stream << "WindowResize: " << std::string(size);
            return stream.str();
        }

        __EventType__(Type::WINDOW_RESIZE);
        __EventCategory__(Category::WINDOW);
    private:
        Math::Unsigned2 size;
    };

    class Event::WindowMove: public Event {
    public:
        WindowMove(const Math::Int2& position): position(position) {}

        int GetX() const { return position.x; }
        int GetY() const { return position.y; }
        Math::Int2 GetPosition() const { return position; }

        operator std::string() const override {
            std::stringstream stream;
            stream << "WindowMove: " << std::string(position);
            return stream.str();
        }

        __EventType__(Type::WINDOW_MOVE);
        __EventCategory__(Category::WINDOW);
    private:
        Math::Int2 position;
    };

    class Event::WindowFocus: public Event {
    public:
        __EventString__("WindowFocus");
        __EventType__(Type::WINDOW_FOCUS);
        __EventCategory__(Category::WINDOW);
    };

    class Event::WindowUnfocus: public Event {
    public:
        __EventString__("WindowUnfocus");
        __EventType__(Type::WINDOW_UNFOCUS);
        __EventCategory__(Category::WINDOW);
    };

    class Event::WindowHover: public Event {
    public:
        __EventString__("WindowHover");
        __EventType__(Type::WINDOW_HOVER);
        __EventCategory__(Category::WINDOW);
    };

    class Event::WindowUnhover: public Event {
    public:
        __EventString__("WindowUnhover");
        __EventType__(Type::WINDOW_UNHOVER);
        __EventCategory__(Category::WINDOW);
    };

    class Event::WindowClose: public Event {
    public:
        __EventString__("WindowClose");
        __EventType__(Type::WINDOW_CLOSE);
        __EventCategory__(Category::WINDOW);
    };


    class __Mouse__: public Event {
    public:
        Input::Mouse GetButton() const { return button; }

        __EventCategory__(Category::INPUT | Category::MOUSE);
    protected:
        Input::Mouse button;

        __Mouse__(Input::Mouse button): button(button) {}
    };

    class Event::MousePress: public __Mouse__ {
    public:
        MousePress(Input::Mouse button): __Mouse__(button) {}

        operator std::string() const override {
            std::stringstream stream;
            stream << "MousePress: " << button;
            return stream.str();
        }

        __EventType__(Type::MOUSE_PRESS);
    };

    class Event::MouseRelease: public __Mouse__ {
    public:
        MouseRelease(Input::Mouse button): __Mouse__(button) {}

        operator std::string() const override {
            std::stringstream stream;
            stream << "MouseRelease: " << button;
            return stream.str();
        }

        __EventType__(Type::MOUSE_RELEASE);
    };

    class Event::MouseScroll: public Event {
    public:
        MouseScroll(const Math::Double2& offset): offset(offset) {}

        double GetX() const { return offset.x; }
        double GetY() const { return offset.y; }
        Math::Double2 GetOffset() const { return offset; }

        operator std::string() const override {
            std::stringstream stream;
            stream << "MouseScroll: " << std::string(offset);
            return stream.str();
        }

        __EventType__(Type::MOUSE_SCROLL);
        __EventCategory__(Category::INPUT | Category::MOUSE);
    private:
        Math::Double2 offset;
    };

    class Event::MouseMove: public Event {
    public:
        MouseMove(const Math::Double2& position): position(position) {} 

        double GetX() const { return position.x; }
        double GetY() const { return position.y; }
        Math::Double2 GetPosition() const { return position; }

        operator std::string() const override {
            std::stringstream stream;
            stream << "MouseMove: " << std::string(position);
            return stream.str();
        }

        __EventType__(Type::MOUSE_MOVE);
        __EventCategory__(Category::INPUT | Category::MOUSE);
    private:
        Math::Double2 position;
    };


    class __Key__: public Event {
    public:
        Input::Key GetKey() const { return key; }

        __EventCategory__(Category::INPUT | Category::KEY);
    protected:
        Input::Key key;

        __Key__(Input::Key key): key(key) {}
    };

    class Event::KeyPress: public __Key__ {
    public:
        KeyPress(Input::Key key, bool repeat): __Key__(key), repeat(repeat) {}

        bool GetRepeat() const { return repeat; }

        operator std::string() const override {
            std::stringstream stream;
            stream << "KeyPress: [" << key << ", " << repeat << ']';
            return stream.str();
        }

        __EventType__(Type::KEY_PRESS);
    private:
        bool repeat;
    };

    class Event::KeyRelease: public __Key__ {
    public:
        KeyRelease(Input::Key key): __Key__(key) {}

        operator std::string() const override {
            std::stringstream stream;
            stream << "KeyRelease: " << key;
            return stream.str();
        }

        __EventType__(Type::KEY_RELEASE);
    };
}
