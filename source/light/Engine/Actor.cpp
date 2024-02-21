#include <light/Engine/Actor.hpp>

namespace light
{
    void
    Actor::attach_part(u32 part)
    {
        u32 mask = 1u << part;

        parts |= mask;
    }

    void
    Actor::detach_part(u32 part)
    {
        u32 mask = 1u << part;

        parts &= ~mask;
    }
} // light
