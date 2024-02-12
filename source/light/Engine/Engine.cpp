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
    f32
    get_time(f32 last)
    {
        f32 time = sdl::get_ticks() / 1000.f;

        if ( last > time )
            return 0;

        return time - last;
    }

    bool
    Engine::execute(State* state, u32 frame_rate)
    {
        f32 step = 1.f / frame_rate;
        f32 time = 0;
        u32 skip = 0;

        if ( state == 0 ) return false;

        state->startup();

        for ( u32 frame = 0; true; frame += 1u ) {
            time = get_time(time);

            if ( time < step ) skip += 1u;

            if ( state->input() == false )
                break;

            for ( ; time >= step; time -= step ) {
                state->fixed_step(step * (skip + 1));

                if ( skip != 0 )
                    skip = 0;
            }

            state->after_step();
        }

        state->cleanup();

        return true;
    }
} // light
