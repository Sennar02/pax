#include <light/Engine/Engine.hpp>

namespace light
{
    Engine::Engine() {}

    bool
    Engine::execute(State* state, u64 frame_rate)
    {
        f64 step = 1.0 / frame_rate;
        f64 time = 0;

        if ( state == 0 ) return false;

        state->startup();

        while ( true ) {
            timer.update();

            time += timer.delta();

            if ( state->input() ) {
                for ( ; time >= step; time -= step )
                    state->fixed_step(step);

                state->after_step();
            } else break;
        }

        state->cleanup();

        return true;
    }
} // light
