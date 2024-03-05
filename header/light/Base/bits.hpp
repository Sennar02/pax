#ifndef LIGHT_BASE_BITS_HPP
#define LIGHT_BASE_BITS_HPP

#include <light/Base/define.hpp>

namespace light
{
    /**
     * Sets the bits specified in the mask to a particular state.
     */
    u64
    bits_write(u64 number, u64 mask, u8 state);

    /**
     * Flips the value of the bits specified in the mask.
     */
    u64
    bits_flip(u64 number, u64 mask);

    /**
     * Returns the exact values of the bits specified in the mask.
     */
    u64
    bits_read(u64 mask, u64 bits);

    /**
     * Determines if the bits specified in the mask are all active.
     */
    bool
    bits_test(u64 mask, u64 bits);
} // light

#endif // LIGHT_BASE_BITS_HPP
