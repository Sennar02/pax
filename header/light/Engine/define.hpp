#ifndef LIGHT_ENGINE_DEFINE_HPP
#define LIGHT_ENGINE_DEFINE_HPP

#include <light/Memory/import.hpp>

namespace light
{
    /**
     * Interface used to program the engine.
     */
    struct State;

    /**
     * Core of the application, uses a state machine
     * to coordinate its states.
     */
    struct Engine;

    struct Camera;
};

#endif // LIGHT_ENGINE_DEFINE_HPP
