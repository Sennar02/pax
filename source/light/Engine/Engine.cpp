#include <light/Engine/Engine.hpp>

namespace sdl
{
    using namespace light;

    f64
    get_seconds()
    {
        return SDL_GetTicks() / 1000.0;
    }
} // sdl

namespace light
{
    Timer::Timer()
        : time {0}
        , last {0}
    {}

    f64
    Timer::elapsed()
    {
        last = time;
        time = sdl::get_seconds();

        if ( time < last )
            return time - (last - time);

        return time - last;
    }

    Engine::Engine()
        : timer {}
    {}

    bool
    Engine::execute(State* state, u64 frame_rate)
    {
        f64 step = 1.0 / frame_rate;
        f64 time = 0;

        if ( state == 0 ) return false;

        state->startup();

        while ( true ) {
            time += timer.elapsed();

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
