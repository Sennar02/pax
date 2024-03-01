#ifndef LIGHT_ENGINE_TIMER_HPP
#define LIGHT_ENGINE_TIMER_HPP

#include <light/Engine/define.hpp>

namespace light
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
        void
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
} // light

#endif // LIGHT_ENGINE_TIMER_HPP
