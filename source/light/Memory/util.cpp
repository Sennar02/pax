#include <light/Memory/util.hpp>

namespace light
{
    bool
    is_power_of_two(u8 bits)
    {
        u8 mask = bits & (bits - 1u);

        return bits != 0 &&
               mask == 0;
    }

    uptr
    round_diff(void* addr, uptr bits, uptr base)
    {
        uptr next = (uptr) addr + base;
        uptr dist = next & (bits - 1u);

        base += (dist != 0) * (bits - dist);

        return base;
    }
} // light
