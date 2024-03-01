#ifndef LIGHT_ENGINE_DEFINE_HPP
#define LIGHT_ENGINE_DEFINE_HPP

#include <light/Memory/import.hpp>
#include <SDL2/SDL.h>

namespace light
{
    /**
     * Interface used to program the engine.
     */
    struct State;

    /**
     * Calculates the seconds elapsed from the start
     * or the application or from the last update.
     */
    struct Timer;

    /**
     * Core of the application, uses a state machine
     * to coordinate its states.
     */
    struct Engine;

    /**
     * Determines the visible portion of the world.
     */
    struct View;

    struct Grid_Layer;
    struct Grid;

    struct Display;
    struct Painter;
};

#endif // LIGHT_ENGINE_DEFINE_HPP
