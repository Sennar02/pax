#ifndef PAX_ENGINE_MONITOR_HPP
#define PAX_ENGINE_MONITOR_HPP

#include <pax/Engine/define.hpp>

namespace pax
{
    struct Monitor
    {
    public:
        /**
         * todo: Comment.
         */
        u64 index = 0;

    public:
        /**
         * todo: Comment.
         */
        bool
        is_valid() const;

        /**
         * todo: Comment.
         */
        v2u64
        size() const;

        /**
         * todo: Comment.
         */
        v4u64
        rect() const;
    };
} // pax

#endif // PAX_ENGINE_MONITOR_HPP
