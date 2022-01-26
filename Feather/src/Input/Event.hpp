#pragma once


#include "Precompiled.hpp"
#include "Input/Mouse.hpp"
#include "Input/Key.hpp"


#define Bind(function) [this](auto&&... args)->decltype(auto) { return this->function(std::forward<decltype(args)>(args)...); }

#define __EventType__(type)                                     \
    static Type GetStaticType() { return type; }                \
    Type GetType() const override { return GetStaticType(); }   \

#define __EventString__(str) operator std::string() const override { return str; }

#define __EventCategory__(category) Category GetCategory() const override { return category; }


// TODO: Use EventBus
// TODO: Use Float2
namespace Feather::Event {
    enum class Type { NONE, WINDOW_RESIZE, WINDOW_ENTER, WINDOW_LEAVE, WINDOW_CLOSE, MOUSE_PRESS, MOUSE_RELEASE, MOUSE_SCROLL, MOUSE_MOVE, KEY_PRESS, KEY_RELEASE, };
    
    enum class Category {
        NONE     = 0,
        WINDOW   = 1 << 0,
        INPUT    = 1 << 1,
        MOUSE    = 1 << 2,
        KEY      = 1 << 3,
    };

    inline Category operator |(Category first, Category second) { return Category(int(first) | int(second)); }
    inline bool operator &(Category first, Category second) { return int(first) & int(second); }


    class Event {
    public:
        bool handled = false;

        virtual ~Event() = default;

        bool In(Category category) { return GetCategory() & category; }

        virtual Type GetType() const = 0;
        virtual Category GetCategory() const = 0;

        // TODO: Use operator <<()
        virtual operator std::string() const { return "Event"; }
    };


    class Dispatcher {
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


    class WindowResize: public Event {
    public:
        WindowResize(unsigned width, unsigned height): width(width), height(height) {}

        unsigned GetWidth() const { return width; }
        unsigned GetHeight() const { return height; }

        operator std::string() const override { 
            std::stringstream stream;
            stream << "WindowResize: " << width << ", " << height;
            return stream.str();
        }

        __EventType__(Type::WINDOW_RESIZE)
        __EventCategory__(Category::WINDOW)
    private:
        unsigned width, height;
    };

    class WindowEnter: public Event {
    public:
        __EventString__("WindowEnter")
        __EventType__(Type::WINDOW_ENTER)
        __EventCategory__(Category::WINDOW)
    };

    class WindowLeave: public Event {
    public:
        __EventString__("WindowLeave")
        __EventType__(Type::WINDOW_LEAVE)
        __EventCategory__(Category::WINDOW)
    };

    class WindowClose: public Event {
    public:
        __EventString__("WindowClose")
        __EventType__(Type::WINDOW_CLOSE)
        __EventCategory__(Category::WINDOW)
    };


    class __Mouse__: public Event {
    public:
        Mouse GetButton() const { return button; }

        __EventCategory__(Category::INPUT | Category::MOUSE)
    protected:
        Mouse button;

        __Mouse__(Mouse button): button(button) {}
    };

    class MousePress: public __Mouse__ {
    public:
        MousePress(Mouse button): __Mouse__(button) {}

        operator std::string() const override {
            std::stringstream stream;
            stream << "MousePress: " << button;
            return stream.str();
        }

        __EventType__(Type::MOUSE_PRESS)
    };

    class MouseRelease: public __Mouse__ {
    public:
        MouseRelease(Mouse button): __Mouse__(button) {}

        operator std::string() const override {
            std::stringstream stream;
            stream << "MouseRelease: " << button;
            return stream.str();
        }

        __EventType__(Type::MOUSE_RELEASE)
    };

    class MouseScroll: public Event {
    public:
        MouseScroll(float xoffset, float yoffset): xoffset(xoffset), yoffset(yoffset) {}

        float GetXOffset() const { return xoffset; }
        float GetYOffset() const { return yoffset; }

        operator std::string() const override {
            std::stringstream stream;
            stream << "MouseScroll: " << xoffset << ", " << yoffset;
            return stream.str();
        }

        __EventType__(Type::MOUSE_SCROLL)
        __EventCategory__(Category::INPUT | Category::MOUSE)
    private:
        float xoffset, yoffset;
    };

    class MouseMove: public Event {
    public:
        MouseMove(float x, float y): x(x), y(y) {} 

        float GetX() const { return x; }
        float GetY() const { return y; }

        operator std::string() const override {
            std::stringstream stream;
            stream << "MouseMove: " << x << ", " << y;
            return stream.str();
        }

        __EventType__(Type::MOUSE_MOVE)
        __EventCategory__(Category::INPUT | Category::MOUSE)
    private:
        float x, y;
    };


    class __Key__: public Event {
    public:
        Key GetKey() const { return key; }

        __EventCategory__(Category::INPUT | Category::KEY)
    protected:
        Key key;

        __Key__(Key key): key(key) {}
    };

    class KeyPress: public __Key__ {
    public:
        KeyPress(Key key, bool repeat): __Key__(key), repeat(repeat) {}

        operator std::string() const override {
            std::stringstream stream;
            stream << "KeyPress: " << key << ", " << repeat;
            return stream.str();
        }

        __EventType__(Type::KEY_PRESS)
    private:
        bool repeat;
    };

    class KeyRelease: public __Key__ {
    public:
        KeyRelease(Key key): __Key__(key) {}

        operator std::string() const override {
            std::stringstream stream;
            stream << "KeyRelease: " << key;
            return stream.str();
        }

        __EventType__(Type::KEY_RELEASE)
    };
}
