#include <light/Engine/Engine.hpp>

namespace sdl
{
    using namespace light;

    u32
    get_ticks()
    {
        return SDL_GetTicks();
    }
} // sdl

namespace light
{
    Timer::Timer()
        : last {0}
        , time {0}
    {}

    f32
    Timer::elapsed()
    {
        last = time;
        time = sdl::get_ticks();

        if ( time < last ) {
            time = time + (MAX_U32 - last);
            last = 0;
        }

        return (time - last) / 1000.f;
    }

    Engine::Engine()
        : timer {}
    {}

    bool
    Engine::execute(State* state, u32 frame_rate)
    {
        f32 step = 1.f / frame_rate;
        f32 time = 0;
        u32 skip = 0;

        if ( state == 0 ) return false;

        state->startup();

        for ( u32 frame = 0; true; frame += 1u ) {
            time += timer.elapsed();

            if ( time < step ) skip += 1u;

            if ( state->input() ) {
                for ( ; time >= step; time -= step ) {
                    state->fixed_step(step, skip + 1u);

                    if ( skip != 0 )
                        skip = 0;
                }

                state->after_step();
            } else break;
        }

        state->cleanup();

        return true;
    }
} // light
