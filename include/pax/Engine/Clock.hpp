#ifndef PAX_ENGINE_CLOCK_HPP
#define PAX_ENGINE_CLOCK_HPP

#include <pax/Engine/define.hpp>

namespace pax
{
    struct Clock
    {
    public:
        /**
         * todo: Comment.
         */
        u64 prev = 0;

        /**
         * todo: Comment.
         */
        u64 time = 0;

    public:
        /**
         * todo: Comment.
         */
        Clock&
        update();

        /**
         * todo: Comment.
         */
        f64
        delta() const;

        /**
         * todo: Comment.
         */
        f64
        total() const;
    };
} // pax

#endif // PAX_ENGINE_CLOCK_HPP
