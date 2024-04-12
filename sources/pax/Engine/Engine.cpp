#include <pax/Engine/Engine.hpp>

// SDL_Init, SDL_Quit.
#include <SDL2/SDL.h>

namespace pax
{
    bool
    Engine::loop(State& state, f64 frame_rate)
    {
        const f64 unit = 1.0 / frame_rate;
        f64       time = 0;

        if ( startup() == false ) return false;

        state.acquire();
        clock.update();

        while ( true ) {
            time += clock.update().delta();

            if ( state.input() ) {
                for ( ; time >= unit; time -= unit )
                    state.fixed_step(unit);

                state.after_step();
            } else break;
        }

        state.release();

        cleanup();

        return true;
    }

    bool
    Engine::startup()
    {
        return SDL_Init(SDL_INIT_VIDEO) == 0;
    }

    bool
    Engine::cleanup()
    {
        SDL_Quit();

        return true;
    }
} // pax
