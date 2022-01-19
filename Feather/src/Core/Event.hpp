#pragma once


#include "Precompiled.hpp"
#include "Input/Mouse.hpp"
#include "Input/Key.hpp"


#define __event_type__(type)                                        \
    static Type get_static_type() { return type; }                  \
    Type get_type() const override { return get_static_type(); }    \

#define __event_string__(str) operator std::string() const override { return str; }

#define __event_category__(category) Category get_category() const override { return category; }


// TODO: Event Bus
namespace Feather::Event {
    enum class Type { NONE, WINDOW_RESIZE, WINDOW_ENTER, WINDOW_LEAVE, WINDOW_CLOSE, MOUSE_PRESS, MOUSE_RELEASE, MOUSE_SCROLL, MOUSE_MOVE, KEY_PRESS, KEY_RELEASE, };
    
    enum class Category {
        NONE     = 0,
        WINDOW   = 1 << 0,
        INPUT    = 1 << 1,
        MOUSE    = 1 << 2,
        KEY      = 1 << 3,
    };

    inline Category operator|(Category first, Category second) { return Category(int(first) | int(second)); }
    inline bool operator&(Category first, Category second) { return int(first) & int(second); }


    class Base {
        friend class Dispatcher;

    public:
        virtual ~Base() = default;

        bool in_category(Category category) { return get_category() & category; }

        virtual Type get_type() const = 0;
        virtual Category get_category() const = 0;

        virtual operator std::string() const { return "Event"; }
    private:
        bool handled = false;
    };


    class Dispatcher {
    public:
        Dispatcher(Base& event_): event(event_) {}

        template<typename T> bool dispatch(std::function<bool (T&)> callback) {
            if (event.get_type() == T::get_static_type()) {
                event.handled |= callback((T&)event);
                return true;
            }
            return false;
        }
    private:
        Base& event;
    };


    // Window

    class WindowResize: public Base {
    public:
        WindowResize(unsigned width_, unsigned height_): width(width_), height(height_) {}

        unsigned get_width() const { return width; }
        unsigned get_height() const { return height; }

        operator std::string() const override { 
            std::stringstream stream;
            stream << "WindowResize: " << width << ", " << height;
            return stream.str();
        }

        __event_type__(Type::WINDOW_RESIZE)
        __event_category__(Category::WINDOW)
    private:
        unsigned width, height;
    };

    class WindowEnter: public Base {
    public:
        __event_string__("WindowEnter")
        __event_type__(Type::WINDOW_ENTER)
        __event_category__(Category::WINDOW)
    };

    class WindowLeave: public Base {
    public:
        __event_string__("WindowLeave")
        __event_type__(Type::WINDOW_LEAVE)
        __event_category__(Category::WINDOW)
    };

    class WindowClose: public Base {
    public:
        __event_string__("WindowClose")
        __event_type__(Type::WINDOW_CLOSE)
        __event_category__(Category::WINDOW)
    };


    // Mouse

    class MouseBase: public Base {
    public:
        Mouse get_button() const { return button; }

        __event_category__(Category::INPUT | Category::MOUSE)
    protected:
        Mouse button;

        MouseBase(Mouse button_): button(button_) {}
    };

    class MousePress: public MouseBase {
    public:
        MousePress(Mouse button): MouseBase(button) {}

        operator std::string() const override { 
            std::stringstream stream;
            stream << "MousePress: " << button;
            return stream.str();
        }

        __event_type__(Type::MOUSE_PRESS)
    };

    class MouseRelease: public MouseBase {
    public:
        MouseRelease(Mouse button): MouseBase(button) {}

        operator std::string() const override { 
            std::stringstream stream;
            stream << "MouseRelease: " << button;
            return stream.str();
        }

        __event_type__(Type::MOUSE_RELEASE)
    };

    class MouseScroll: public Base {
    public:
        MouseScroll(float x_offset_, float y_offset_): x_offset(x_offset_), y_offset(y_offset_) {}

        float get_x_offset() const { return x_offset; }
        float get_y_offset() const { return y_offset; }

        operator std::string() const override { 
            std::stringstream stream;
            stream << "MouseScroll: " << x_offset << ", " << y_offset;
            return stream.str();
        }

        __event_type__(Type::MOUSE_SCROLL)
        __event_category__(Category::INPUT | Category::MOUSE)
    private:
        float x_offset, y_offset;
    };

    class MouseMove: public Base {
    public:
        MouseMove(float x_, float y_): x(x_), y(y_) {} 

        float get_x() const { return x; }
        float get_y() const { return y; }

        operator std::string() const override { 
            std::stringstream stream;
            stream << "MouseMove: " << x << ", " << y;
            return stream.str();
        }

        __event_type__(Type::MOUSE_MOVE)
        __event_category__(Category::INPUT | Category::MOUSE)
    private:
        float x, y;
    };


    // Key

    class KeyBase: public Base {
    public:
        Key get_key() const { return key; }

        __event_category__(Category::INPUT | Category::KEY)
    protected:
        Key key;

        KeyBase(Key key_): key(key_) {}
    };

    class KeyPress: public KeyBase {
    public:
        KeyPress(Key key): KeyBase(key) {}

        operator std::string() const override { 
            std::stringstream stream;
            stream << "KeyPress: " << key;
            return stream.str();
        }

        __event_type__(Type::KEY_PRESS)
    };

    class KeyRelease: public KeyBase {
    public:
        KeyRelease(Key key): KeyBase(key) {}

        operator std::string() const override { 
            std::stringstream stream;
            stream << "KeyRelease: " << key;
            return stream.str();
        }

        __event_type__(Type::KEY_RELEASE)
    };
}
