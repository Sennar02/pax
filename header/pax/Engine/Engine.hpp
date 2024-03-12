#ifndef PAX_ENGINE_ENGINE_HPP
#define PAX_ENGINE_ENGINE_HPP

#include <pax/Engine/define.hpp>
#include <pax/Engine/Kernel/State.hpp>
#include <pax/Engine/Kernel/Timer.hpp>

namespace pax
{
    struct Engine
    {
    public:
        /**
         *
         */
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
} // pax

#endif // PAX_ENGINE_ENGINE_HPP
