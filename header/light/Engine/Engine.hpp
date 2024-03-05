#ifndef LIGHT_ENGINE_ENGINE_HPP
#define LIGHT_ENGINE_ENGINE_HPP

#include <light/Engine/define.hpp>
#include <light/Engine/State.hpp>
#include <light/Engine/Timer.hpp>

namespace light
{
    struct Engine
    {
    public:
        Timer timer = {};

    public:
        /**
         *
         */
        Engine();

        /**
         *
         */
        bool
        execute(State& state, u64 frames);
    };
} // light

#endif // LIGHT_ENGINE_ENGINE_HPP
