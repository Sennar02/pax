#include <light/Base/bits.hpp>

namespace light
{
    u64
    bit_write(u64 mask, u64 bits, u8 state)
    {
        return light_bit_set(mask, bits) * (state != 0) +
               light_bit_clr(mask, bits) * (state == 0);
    }

    u64
    bit_negate(u64 mask, u64 bits)
    {
        u64 state = mask & bits;

        return light_bit_set(mask, bits) * (state == 0) +
               light_bit_clr(mask, bits) * (state != 0);
    }

    u64
    bit_read(u64 mask, u64 bits)
    {
        return mask & bits;
    }

    bool
    bit_test(u64 mask, u64 bits)
    {
        return (mask & bits) == bits;
    }
} // light
