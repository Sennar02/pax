#ifndef LIGHT_MEMORY_UTIL_HPP
#define LIGHT_MEMORY_UTIL_HPP

#include <light/Memory/define.hpp>

namespace light
{
    bool
    is_power_of_two(u8 bits);

    uptr
    round_diff(void* addr, uptr bits, uptr base);
} // light

#endif // LIGHT_MEMORY_UTIL_HPP
