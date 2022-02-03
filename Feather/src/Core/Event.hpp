#pragma once


#include "Precompiled.hpp"
#include "Math/Vector.hpp"
#include "Input/Mouse.hpp"
#include "Input/Key.hpp"


#define Bind(function) [this](auto&&... args)->decltype(auto) { return this->function(std::forward<decltype(args)>(args)...); }

#define __EventType__(type)                                     \
    static Type GetStaticType() { return type; }                \
    Type GetType() const override { return GetStaticType(); }   \

#define __EventString__(str) operator std::string() const override { return str; }

#define __EventCategory__(category) Category GetCategory() const override { return category; }


namespace Feather::Event {
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

    inline Category operator|(Category first, Category second) { return Category(int(first) | int(second)); }
    inline bool operator&(Category first, Category second) { return int(first) & int(second); }


    class Event {
    public:
        bool handled = false;

        virtual ~Event() = default;

        bool In(Category category) { return GetCategory() & category; }

        virtual Type GetType() const = 0;
        virtual Category GetCategory() const = 0;

        // TODO: Use operator<<()
        virtual operator std::string() const { return "Event"; }
    };


    // TODO: Use an EventBus
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
        WindowResize(Math::Vector2 size): size(size) {}

        float GetWidth() const { return size.x; }
        float GetHeight() const { return size.y; }
        Math::Vector2 GetSize() const { return size; }

        operator std::string() const override {
            std::stringstream stream;
            stream << "WindowResize: " << std::string(size);
            return stream.str();
        }

        __EventType__(Type::WINDOW_RESIZE);
        __EventCategory__(Category::WINDOW);
    private:
        Math::Vector2 size;
    };

    class WindowMove: public Event {
    public:
        WindowMove(Math::Vector2 position): position(position) {}

        float GetX() const { return position.x; }
        float GetY() const { return position.y; }
        Math::Vector2 GetPosition() const { return position; }

        operator std::string() const override {
            std::stringstream stream;
            stream << "WindowMove: " << std::string(position);
            return stream.str();
        }

        __EventType__(Type::WINDOW_MOVE);
        __EventCategory__(Category::WINDOW);
    private:
        Math::Vector2 position;
    };

    class WindowFocus: public Event {
    public:
        __EventString__("WindowFocus");
        __EventType__(Type::WINDOW_FOCUS);
        __EventCategory__(Category::WINDOW);
    };

    class WindowUnfocus: public Event {
    public:
        __EventString__("WindowUnfocus");
        __EventType__(Type::WINDOW_UNFOCUS);
        __EventCategory__(Category::WINDOW);
    };

    class WindowHover: public Event {
    public:
        __EventString__("WindowHover");
        __EventType__(Type::WINDOW_HOVER);
        __EventCategory__(Category::WINDOW);
    };

    class WindowUnhover: public Event {
    public:
        __EventString__("WindowUnhover");
        __EventType__(Type::WINDOW_UNHOVER);
        __EventCategory__(Category::WINDOW);
    };

    class WindowClose: public Event {
    public:
        __EventString__("WindowClose");
        __EventType__(Type::WINDOW_CLOSE);
        __EventCategory__(Category::WINDOW);
    };


    class __Mouse__: public Event {
    public:
        Mouse GetButton() const { return button; }

        __EventCategory__(Category::INPUT | Category::MOUSE);
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

        __EventType__(Type::MOUSE_PRESS);
    };

    class MouseRelease: public __Mouse__ {
    public:
        MouseRelease(Mouse button): __Mouse__(button) {}

        operator std::string() const override {
            std::stringstream stream;
            stream << "MouseRelease: " << button;
            return stream.str();
        }

        __EventType__(Type::MOUSE_RELEASE);
    };

    class MouseScroll: public Event {
    public:
        MouseScroll(Math::Vector2 offset): offset(offset) {}

        float GetX() const { return offset.x; }
        float GetY() const { return offset.y; }
        Math::Vector2 GetOffset() const { return offset; }

        operator std::string() const override {
            std::stringstream stream;
            stream << "MouseScroll: " << std::string(offset);
            return stream.str();
        }

        __EventType__(Type::MOUSE_SCROLL);
        __EventCategory__(Category::INPUT | Category::MOUSE);
    private:
        Math::Vector2 offset;
    };

    class MouseMove: public Event {
    public:
        MouseMove(Math::Vector2 position): position(position) {} 

        float GetX() const { return position.x; }
        float GetY() const { return position.y; }
        Math::Vector2 GetPosition() const { return position; }

        operator std::string() const override {
            std::stringstream stream;
            stream << "MouseMove: " << std::string(position);
            return stream.str();
        }

        __EventType__(Type::MOUSE_MOVE);
        __EventCategory__(Category::INPUT | Category::MOUSE);
    private:
        Math::Vector2 position;
    };


    class __Key__: public Event {
    public:
        Key GetKey() const { return key; }

        __EventCategory__(Category::INPUT | Category::KEY);
    protected:
        Key key;

        __Key__(Key key): key(key) {}
    };

    class KeyPress: public __Key__ {
    public:
        KeyPress(Key key, bool repeat): __Key__(key), repeat(repeat) {}

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

    class KeyRelease: public __Key__ {
    public:
        KeyRelease(Key key): __Key__(key) {}

        operator std::string() const override {
            std::stringstream stream;
            stream << "KeyRelease: " << key;
            return stream.str();
        }

        __EventType__(Type::KEY_RELEASE);
    };
}
