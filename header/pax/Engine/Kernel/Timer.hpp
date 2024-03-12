#ifndef PAX_ENGINE_TIMER_HPP
#define PAX_ENGINE_TIMER_HPP

#include <pax/Engine/define.hpp>

namespace pax
{
    struct Timer
    {
    public:
        /**
         *
         */
        f64 prev = 0;

        /**
         *
         */
        f64 last = 0;

    public:
        /**
         *
         */
        Timer&
        update();

        /**
         *
         */
        f64
        total() const;

        /**
         *
         */
        f64
        delta() const;
    };
} // pax

#endif // PAX_ENGINE_TIMER_HPP
