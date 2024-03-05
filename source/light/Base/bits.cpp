#include <light/Base/bits.hpp>

namespace light
{
    u64
    bits_write(u64 number, u64 mask, u8 state)
    {
        return (state != 0) * (number | mask) +
               (state == 0) * (number & ~mask);
    }

    u64
    bits_flip(u64 number, u64 mask)
    {
        return number ^ mask;
    }

    u64
    bits_read(u64 number, u64 mask)
    {
        return number & mask;
    }

    bool
    bits_test(u64 number, u64 mask)
    {
        return (number & mask) != 0;
    }
} // light
