#include <pax/Engine/State.hpp>

namespace pax
{
    void
    State::acquire()
    { }

    void
    State::release()
    { }

    void
    State::enter()
    { }

    void
    State::leave()
    { }

    bool
    State::input()
    {
        return false;
    }

    void
    State::fixed_step(f64)
    { }

    void
    State::after_step()
    { }
} // pax