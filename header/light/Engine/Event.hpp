#ifndef LIGHT_ENGINE_EVENT_HPP
#define LIGHT_ENGINE_EVENT_HPP

#include <light/Engine/define.hpp>

namespace light
{
    enum Display_Event_Type
    {
        DISPLAY_OPEN,
        DISPLAY_CLOSE,
        DISPLAY_GAIN_FOCUS,
        DISPLAY_LOSE_FOCUS,
        DISPLAY_MOVE,
        DISPLAY_RESIZE,
    };

    enum Keybd_Event_Type {
        KEYBD_PRESS,
        KEYBD_RELEASE,
    };

    enum Mouse_Event_Type {
        MOUSE_PRESS,
        MOUSE_RELEASE,
        MOUSE_MOVE,
        MOUSE_SCROLL,
    };

    struct Event
    {
    public:
        bool sent = false;

    public:
        /**
         *
         */
        virtual u64
        type() const = 0;

        /**
         *
         */
        virtual u64
        mask() const = 0;
    };

    struct Keybd_Press_Event
        : public Event
    {
    public:
        static const u64 TYPE;

    public:
        u64  physic = 0;
        u64  symbol = 0;
        u64  modifs = 0;
        bool repeat = false;

    public:
        /**
         *
         */
        virtual u64
        type() const;

        /**
         *
         */
        virtual u64
        mask() const;
    };

    struct Keybd_Release_Event
        : public Event
    {
    public:
        static const u64 TYPE;

    public:
        u64 physic = 0;
        u64 symbol = 0;

    public:
        virtual u64
        type() const;

        virtual u64
        mask() const;
    };
} // light

#endif // LIGHT_ENGINE_MESSAGE_HPP
