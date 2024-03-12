#include <pax/Engine/Engine.hpp>

namespace pax
{
    Engine::Engine() {}

    bool
    Engine::execute(State& state, u64 frame_rate)
    {
        f64 step = 1.0 / frame_rate;
        f64 time = 0;
        u64 tick = 0;

        state.startup();
        timer.update();

        while ( true ) {
            time += timer.update().delta();

            if ( state.input() ) {
                for ( tick = 0; time >= step; time -= step )
                    state.fixed_step(step, ++tick);

                state.after_step();
            } else break;
        }

        state.cleanup();

        return true;
    }
} // pax
