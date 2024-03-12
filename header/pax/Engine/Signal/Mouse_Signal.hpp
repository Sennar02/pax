#ifndef PAX_ENGINE_MOUSE_EVENT_HPP
#define PAX_ENGINE_MOUSE_EVENT_HPP

#include <pax/Engine/define.hpp>
#include <pax/Signal/Signal.hpp>

namespace pax
{
    struct Mouse_Signal
        : public Signal
    {
    public:
        enum Flag
        {
            FLAG_PRESS = 0x01,
            FLAG_BTN_L = 0x02,
            FLAG_BTN_M = 0x04,
            FLAG_BTN_R = 0x08,
            FLAG_BTN_X = 0x10,
            FLAG_BTN_Y = 0x20,
        };

        /**
         *
         */
        static const u64 KIND;

    public:
        /**
         *
         */
        v2s64 coords = {};

        /**
         *
         */
        v2s64 motion = {};

        /**
         *
         */
        v2f64 scroll = {};

        /**
         *
         */
        u64 button = 0;

        /**
         *
         */
        u64 clicks = 0;

        /**
         *
         */
        u64 flags = 0;

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

        /**
         *
         */
        bool
        test_btn(u64 index) const;
    };
} // pax

#endif // PAX_ENGINE_MOUSE_EVENT_HPP
