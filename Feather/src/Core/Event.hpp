#pragma once


#include "Precompiled.hpp"
#include "Math/Vector.hpp"
#include "Input/Mouse.hpp"
#include "Input/Key.hpp"


#define BindEvent(function) [this](auto&&... args) -> decltype(auto) { return this->function(std::forward<decltype(args)>(args)...); }


namespace Feather {
    class Event {
    public:
        enum class Category {
            NONE     = 0,
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


        Event(std::size_t type): type(type) {}
        virtual ~Event() = default;


        template<typename T> static std::size_t TypeOf() {
            static const std::size_t type = next++;
            return type;
        }


        std::size_t GetType() { return type; }
        virtual Category GetCategory() const { return Category::NONE; }


        friend Category operator|(Category first, Category second) {
            return Category(static_cast<std::underlying_type<Category>::type>(first) | static_cast<std::underlying_type<Category>::type>(second));
        }

        friend Category operator&(Category first, Category second) {
            return Category(static_cast<std::underlying_type<Category>::type>(first) & static_cast<std::underlying_type<Category>::type>(second));
        }

        bool In(Category category) {
            return static_cast<bool>(GetCategory() & category);
        }


        friend std::ostream& operator<<(std::ostream& stream, const Event& event) { return stream << "Event: " << event.type; }
    private:
        const std::size_t type;
        inline static std::size_t next = 0;
    };


    // TODO: Event Bus
    class Event::Dispatcher {
    public:
        Dispatcher(Event& event): event(event) {}

        template<typename T, typename F> bool Dispatch(const F& callback) {
            if (event.GetType() == TypeOf<T>()) {
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
        WindowResize(const Math::Unsigned2& size): Event(TypeOf<WindowResize>()), size(size) {}

        unsigned GetWidth() const { return size.x; }
        unsigned GetHeight() const { return size.y; }
        Math::Unsigned2 GetSize() const { return size; }

        Category GetCategory() const override { return Category::WINDOW; }
        friend std::ostream& operator<<(std::ostream& stream, const WindowResize& event) { return stream << "Window Resize: " << event.size; }
    private:
        Math::Unsigned2 size;
    };

    class Event::WindowMove: public Event {
    public:
        WindowMove(const Math::Int2& position): Event(TypeOf<WindowMove>()), position(position) {}

        int GetX() const { return position.x; }
        int GetY() const { return position.y; }
        Math::Int2 GetPosition() const { return position; }

        Category GetCategory() const override { return Category::WINDOW; }
        friend std::ostream& operator<<(std::ostream& stream, const WindowMove& event) { return stream << "Window Move: " << event.position; }
    private:
        Math::Int2 position;
    };

    class Event::WindowFocus: public Event {
    public:
        WindowFocus(): Event(TypeOf<WindowFocus>()) {}
        Category GetCategory() const override { return Category::WINDOW; }
        friend std::ostream& operator<<(std::ostream& stream, const WindowFocus& event) { return stream << "Window Focus"; }
    };

    class Event::WindowUnfocus: public Event {
    public:
        WindowUnfocus(): Event(TypeOf<WindowUnfocus>()) {}
        Category GetCategory() const override { return Category::WINDOW; }
        friend std::ostream& operator<<(std::ostream& stream, const WindowUnfocus& event) { return stream << "Window Unfocus"; }
    };

    class Event::WindowHover: public Event {
    public:
        WindowHover(): Event(TypeOf<WindowHover>()) {}
        Category GetCategory() const override { return Category::WINDOW; }
        friend std::ostream& operator<<(std::ostream& stream, const WindowHover& event) { return stream << "Window Hover"; }
    };

    class Event::WindowUnhover: public Event {
    public:
        WindowUnhover(): Event(TypeOf<WindowUnhover>()) {}
        Category GetCategory() const override { return Category::WINDOW; }
        friend std::ostream& operator<<(std::ostream& stream, const WindowUnhover& event) { return stream << "Window Unhover"; }
    };

    class Event::WindowClose: public Event {
    public:
        WindowClose(): Event(TypeOf<WindowClose>()) {}
        Category GetCategory() const override { return Category::WINDOW; }
        friend std::ostream& operator<<(std::ostream& stream, const WindowClose& event) { return stream << "Window Close"; }
    };


    class Event::MousePress: public Event {
    public:
        MousePress(Input::Mouse button): Event(TypeOf<MousePress>()), button(button) {}

        Input::Mouse GetButton() const { return button; }

        Category GetCategory() const override { return Category::INPUT | Category::MOUSE; }
        friend std::ostream& operator<<(std::ostream& stream, const MousePress& event) { return stream << "Mouse Press: " << event.button; }
    private:
        Input::Mouse button;
    };

    class Event::MouseRelease: public Event {
    public:
        MouseRelease(Input::Mouse button): Event(TypeOf<MouseRelease>()), button(button) {}

        Input::Mouse GetButton() const { return button; }

        Category GetCategory() const override { return Category::INPUT | Category::MOUSE; }
        friend std::ostream& operator<<(std::ostream& stream, const MouseRelease& event) { return stream << "Mouse Release: " << event.button; }
    private:
        Input::Mouse button;
    };

    class Event::MouseScroll: public Event {
    public:
        MouseScroll(const Math::Double2& offset): Event(TypeOf<MouseScroll>()),  offset(offset) {}

        double GetX() const { return offset.x; }
        double GetY() const { return offset.y; }
        Math::Double2 GetOffset() const { return offset; }

        Category GetCategory() const override { return Category::INPUT | Category::MOUSE; }
        friend std::ostream& operator<<(std::ostream& stream, const MouseScroll& event) { return stream << "Mouse Scroll: " << event.offset; }
    private:
        Math::Double2 offset;
    };

    class Event::MouseMove: public Event {
    public:
        MouseMove(const Math::Double2& position): Event(TypeOf<MouseMove>()), position(position) {}

        double GetX() const { return position.x; }
        double GetY() const { return position.y; }
        Math::Double2 GetPosition() const { return position; }

        Category GetCategory() const override { return Category::INPUT | Category::MOUSE; }
        friend std::ostream& operator<<(std::ostream& stream, const MouseMove& event) { return stream << "Mouse Move: " << event.position; }
    private:
        Math::Double2 position;
    };


    class Event::KeyPress: public Event {
    public:
        KeyPress(Input::Key key, bool repeat): Event(TypeOf<KeyPress>()), key(key), repeat(repeat) {}

        Input::Key GetKey() const { return key; }
        bool GetRepeat() const { return repeat; }

        Category GetCategory() const override { return Category::INPUT | Category::KEY; }
        friend std::ostream& operator<<(std::ostream& stream, const KeyPress& event) { return stream << "Key Press: [" << event.key << ", " << event.repeat << ']'; }
    private:
        bool repeat;
        Input::Key key;
    };

    class Event::KeyRelease: public Event {
    public:
        KeyRelease(Input::Key key): Event(TypeOf<KeyRelease>()), key(key) {}

        Input::Key GetKey() const { return key; }

        Category GetCategory() const override { return Category::INPUT | Category::KEY; }
        friend std::ostream& operator<<(std::ostream& stream, const KeyRelease& event) { return stream << "Key Release: " << event.key; }
    private:
        Input::Key key;
    };
}
