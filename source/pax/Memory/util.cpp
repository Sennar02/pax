#include <pax/Memory/util.hpp>

namespace pax
{
    bool
    is_power_of_two(u64 bits)
    {
        u64 mask = bits & (bits - 1u);

        return bits != 0 &&
               mask == 0;
    }

    uptr
    align_diff(void* addr, uptr bits, uptr base)
    {
        uptr next = (uptr) addr + base;
        uptr dist = next & (bits - 1u);

        base += (dist != 0) * (bits - dist);

        return base;
    }
} // pax
