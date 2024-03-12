#ifndef PAX_ENGINE_DISPLAY_EVENT_HPP
#define PAX_ENGINE_DISPLAY_EVENT_HPP

#include <pax/Engine/define.hpp>

namespace pax
{
    struct Display_Signal
        : public Signal
    {
    public:
        enum Flag
        {
            FLAG_CLOSE = 0x01,
        };

        /**
         *
         */
        static const u64 KIND;

    public:
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
        is_close() const;
    };
} // pax

#endif // PAX_ENGINE_DISPLAY_EVENT_HPP
