#ifndef PAX_ENGINE_SCREEN_HPP
#define PAX_ENGINE_SCREEN_HPP

#include <pax/Engine/define.hpp>

namespace pax
{
    struct Screen
    {
    public:
        /**
         *
         */
        u64 index = 0;

    public:
        /**
         *
         */
        bool
        is_valid() const;

        /**
         *
         */
        v2u64
        size() const;

        /**
         *
         */
        v4u64
        bounds() const;
    };
} // pax

#endif // PAX_ENGINE_SCREEN_HPP
