#ifndef PAX_ENGINE_STATE_HPP
#define PAX_ENGINE_STATE_HPP

#include <pax/Engine/define.hpp>

namespace pax
{
    struct State
    {
    public:
        /**
         * Default constructor to make the compiler happy.
         */
        State();

        /**
         * Procedure used to initialize the state.
         */
        virtual void
        start() = 0;

        /**
         * Procedure used to finalize the state.
         */
        virtual void
        clean() = 0;

        /**
         * Procedure for the entering state transition.
         */
        virtual void
        enter() = 0;

        /**
         * Procedure for the leaving state transition.
         */
        virtual void
        leave() = 0;

        /**
         * Procedure used to take input and communicate
         * to the state machine the desire to leave or
         * not the execution.
         */
        virtual bool
        input() = 0;

        /**
         * Procedure called from zero to any number of
         * times during one frame, to alter the world
         * state at a consistent rate.
         */
        virtual void
        fixed_step(f64 step, u64 tick) = 0;

        /**
         * Procedure called exactly once during one frame.
         */
        virtual void
        after_step() = 0;
    };
} // pax

#endif // PAX_ENGINE_STATE_HPP
