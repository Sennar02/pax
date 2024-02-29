#ifndef LIGHT_MEMORY_UTIL_HPP
#define LIGHT_MEMORY_UTIL_HPP

#include <light/Memory/define.hpp>

namespace light
{
    /**
     * Determines if the bit mask has exactly
     * one single bit active.
     */
    bool
    is_power_of_two(u64 bits);

    /**
     * Returns the distance in bytes of a memory
     * address from a specific alignment with a
     * minimum base value.
     */
    uptr
    align_diff(void* addr, uptr bits, uptr base);
} // light

#endif // LIGHT_MEMORY_UTIL_HPP
