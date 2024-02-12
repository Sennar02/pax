#ifndef LIGHT_ENGINE_ENGINE_HPP
#define LIGHT_ENGINE_ENGINE_HPP

#include <light/Engine/define.hpp>
#include <light/Engine/State.hpp>

#include <SDL2/SDL_timer.h>

namespace light
{
    struct Engine
    {
    public:
        /**
         *
         */
        bool
        execute(State* state, u32 frames);
    };
} // light

#endif // LIGHT_ENGINE_ENGINE_HPP
