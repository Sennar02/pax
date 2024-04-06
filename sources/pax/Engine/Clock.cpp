#include <pax/Engine/Clock.hpp>

// SDL_GetTicks64
#include <SDL2/SDL_timer.h>

namespace pax
{
    Clock&
    Clock::update()
    {
        prev = time;
        time = SDL_GetTicks64();

        return pax_self;
    }

    f64
    Clock::delta() const
    {
        return (time - prev + 1) / 1000.0;
    }

    f64
    Clock::total() const
    {
        return time / 1000.0;
    }
} // pax
