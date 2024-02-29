#include <light/Base/bits.hpp>

namespace light
{
    u64
    bits_write(u64 mask, u64 bits, u8 state)
    {
        return (state != 0) * light_bits_set(mask, bits) +
               (state == 0) * light_bits_clr(mask, bits);
    }

    u64
    bits_flip(u64 mask, u64 bits)
    {
        u64 state = mask & bits;

        return (state == 0) * light_bits_set(mask, bits) +
               (state != 0) * light_bits_clr(mask, bits);
    }

    u64
    bits_read(u64 mask, u64 bits)
    {
        return mask & bits;
    }

    bool
    bits_test(u64 mask, u64 bits)
    {
        return (mask & bits) == bits;
    }
} // light
