#pragma once


#include "Precompiled.hpp"
#include "Math/Vector.hpp"
#include "Input/Mouse.hpp"
#include "Input/Key.hpp"


#define BindEvent(function) [this](auto&&... args) -> decltype(auto) { return this->function(std::forward<decltype(args)>(args)...); }

#define __EventType__(type)                                     \
    static Type GetStaticType() { return type; }                \
    Type GetType() const override { return GetStaticType(); }   \

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


        friend std::ostream& operator<<(std::ostream& stream, const Event& event) { return stream << "Event"; }
    };


    // TODO: Event Bus
    class Event::Dispatcher {
    public:
        Dispatcher(Event& event): event(event) {}

        template<typename T, typename F> bool Dispatch(const F& callback) {
            if (event.GetType() == T::GetStaticType()) {
                event.handled |= callback(dynamic_cast<T&>(event));
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

        friend std::ostream& operator<<(std::ostream& stream, const WindowResize& event) { return stream << "Window Resize: " << event.size; }

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

        friend std::ostream& operator<<(std::ostream& stream, const WindowMove& event) { return stream << "Window Move: " << event.position; }

        __EventType__(Type::WINDOW_MOVE);
        __EventCategory__(Category::WINDOW);
    private:
        Math::Int2 position;
    };

    class Event::WindowFocus: public Event {
    public:
        friend std::ostream& operator<<(std::ostream& stream, const WindowFocus& event) { return stream << "Window Focus"; }
        __EventType__(Type::WINDOW_FOCUS);
        __EventCategory__(Category::WINDOW);
    };

    class Event::WindowUnfocus: public Event {
    public:
        friend std::ostream& operator<<(std::ostream& stream, const WindowUnfocus& event) { return stream << "Window Unfocus"; }
        __EventType__(Type::WINDOW_UNFOCUS);
        __EventCategory__(Category::WINDOW);
    };

    class Event::WindowHover: public Event {
    public:
        friend std::ostream& operator<<(std::ostream& stream, const WindowHover& event) { return stream << "Window Hover"; }
        __EventType__(Type::WINDOW_HOVER);
        __EventCategory__(Category::WINDOW);
    };

    class Event::WindowUnhover: public Event {
    public:
        friend std::ostream& operator<<(std::ostream& stream, const WindowUnhover& event) { return stream << "Window Unhover"; }
        __EventType__(Type::WINDOW_UNHOVER);
        __EventCategory__(Category::WINDOW);
    };

    class Event::WindowClose: public Event {
    public:
        friend std::ostream& operator<<(std::ostream& stream, const WindowClose& event) { return stream << "Window Close"; }
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

        friend std::ostream& operator<<(std::ostream& stream, const MousePress& event) { return stream << "Mouse Press: " << event.button; }

        __EventType__(Type::MOUSE_PRESS);
    };

    class Event::MouseRelease: public __Mouse__ {
    public:
        MouseRelease(Input::Mouse button): __Mouse__(button) {}

        friend std::ostream& operator<<(std::ostream& stream, const MouseRelease& event) { return stream << "Mouse Release: " << event.button; }

        __EventType__(Type::MOUSE_RELEASE);
    };

    class Event::MouseScroll: public Event {
    public:
        MouseScroll(const Math::Double2& offset): offset(offset) {}

        double GetX() const { return offset.x; }
        double GetY() const { return offset.y; }
        Math::Double2 GetOffset() const { return offset; }

        friend std::ostream& operator<<(std::ostream& stream, const MouseScroll& event) { return stream << "Mouse Scroll: " << event.offset; }

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

        friend std::ostream& operator<<(std::ostream& stream, const MouseMove& event) { return stream << "Mouse Move: " << event.position; }

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

        friend std::ostream& operator<<(std::ostream& stream, const KeyPress& event) { return stream << "Key Press: [" << event.key << ", " << event.repeat << ']'; }

        __EventType__(Type::KEY_PRESS);
    private:
        bool repeat;
    };

    class Event::KeyRelease: public __Key__ {
    public:
        KeyRelease(Input::Key key): __Key__(key) {}

        friend std::ostream& operator<<(std::ostream& stream, const KeyRelease& event) { return stream << "Key Release: " << event.key; }

        __EventType__(Type::KEY_RELEASE);
    };
}
