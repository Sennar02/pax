#ifndef LIGHT_ENGINE_MOUSE_EVENT_HPP
#define LIGHT_ENGINE_MOUSE_EVENT_HPP

#include <light/Engine/define.hpp>
#include <light/Events/Event.hpp>

namespace light
{
    struct Mouse_Event
        : public Event
    {
    public:
        /**
         *
         */
        static const u64 KIND;

        /**
         *
         */
        static const u64 MASK;

    public:
        v2s64 coords = {};
        v2s64 motion = {};
        v2f64 scroll = {};
        u64   button = 0;
        u64   clicks = 0;
        u64   flags  = 0;

        enum Flags {
            PRESS  = 0x01,
            MAIN_L = 0x02,
            MAIN_M = 0x04,
            MAIN_R = 0x08,
            EXTR_1 = 0x10,
            EXTR_2 = 0x20,
        };

    public:
        /**
         *
         */
        u64
        kind() const;

        /**
         *
         */
        bool
        is_press() const;

        /**
         *
         */
        bool
        is_release() const;
    };
} // light

#endif // LIGHT_ENGINE_MOUSE_EVENT_HPP
