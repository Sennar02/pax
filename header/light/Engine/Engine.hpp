#ifndef LIGHT_ENGINE_ENGINE_HPP
#define LIGHT_ENGINE_ENGINE_HPP

#include <light/Engine/define.hpp>
#include <light/Engine/State.hpp>

namespace light
{
    struct Timer
    {
    public:
        f32 time;
        f32 last;

    public:
        /**
         *
         */
        Timer();

        /**
         *
         */
        f32
        elapsed();
    };

    struct Engine
    {
    public:
        Timer timer;

    public:
        /**
         *
         */
        Engine();

        /**
         *
         */
        bool
        execute(State* state, u32 frames);
    };
} // light

#endif // LIGHT_ENGINE_ENGINE_HPP
