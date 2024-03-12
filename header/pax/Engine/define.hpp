#ifndef PAX_ENGINE_DEFINE_HPP
#define PAX_ENGINE_DEFINE_HPP

#include <pax/Signal/import.hpp>
#include <pax/Memory/import.hpp>
#include <SDL2/SDL.h>

namespace pax
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

    /**
     *
     */
    struct Grid_Layer;

    /**
     *
     */
    struct Grid;

    /**
     *
     */
    struct Display;

    /**
     *
     */
    struct Painter;

    /**
     *
     */
    struct Screen;

    enum Signal_Kind
    {
        DISPLAY = 1,
        KEYBD   = 2,
        MOUSE   = 3,
    };

    /**
     *
     */
    struct Keybd_Signal;

    /**
     *
     */
    struct Mouse_Signal;

    /**
     *
     */
    struct Signal_System_Source;
};

#endif // PAX_ENGINE_DEFINE_HPP
