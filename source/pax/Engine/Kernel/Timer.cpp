#include <pax/Engine/Kernel/Timer.hpp>

namespace pax
{
    Timer&
    Timer::update()
    {
        prev = last;
        last = SDL_GetTicks() / 1000.0;

        return *this;
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
} // pax
