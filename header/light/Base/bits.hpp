#ifndef LIGHT_BASE_BITS_HPP
#define LIGHT_BASE_BITS_HPP

#include <light/Base/define.hpp>

namespace light
{
    u64
    bit_write(u64 mask, u64 bits, u8 state);

    u64
    bit_negate(u64 mask, u64 bits);

    u64
    bit_read(u64 mask, u64 bits);

    bool
    bit_test(u64 mask, u64 bits);
} // light

#define light_bit_set(mask, bits) \
    (mask | bits)

#define light_bit_clr(mask, bits) \
    (mask & ~bits)

#endif // LIGHT_BASE_BITS_HPP
