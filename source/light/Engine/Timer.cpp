#include <light/Engine/Timer.hpp>

namespace light
{
    void
    Timer::update()
    {
        prev = last;
        last = SDL_GetTicks() / 1000.0;
    }

    f64
    Timer::total() const
    {
        return last;
    }

    f64
    Timer::delta() const
    {
        return last - prev;
    }
} // light
