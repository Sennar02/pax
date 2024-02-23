#ifndef LIGHT_ENGINE_DEFINE_HPP
#define LIGHT_ENGINE_DEFINE_HPP

#include <light/Memory/import.hpp>
#include <SDL2/SDL.h>

namespace light
{
    struct Actor;

    /**
     * Interface used to program the engine.
     */
    struct State;

    /**
     * Core of the application, uses a state machine
     * to coordinate its states.
     */
    struct Engine;

    struct View;
    struct Display;
    struct Painter;
};

#endif // LIGHT_ENGINE_DEFINE_HPP
