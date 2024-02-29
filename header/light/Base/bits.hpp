#ifndef LIGHT_BASE_BITS_HPP
#define LIGHT_BASE_BITS_HPP

#include <light/Base/define.hpp>

namespace light
{
    /**
     * Sets the value of each bit in the mask
     * specified by another to a specific state.
     */
    u64
    bits_write(u64 mask, u64 bits, u8 state);

    /**
     * Negates the value of each bit in the
     * mask specified by another.
     */
    u64
    bits_flip(u64 mask, u64 bits);

    /**
     * Returns the exact values for each bit
     * in the mask.
     */
    u64
    bits_read(u64 mask, u64 bits);

    /**
     * Determines if every bit in the mask is
     * activated.
     */
    bool
    bits_test(u64 mask, u64 bits);
} // light

/**
 * Adds a mask of bits to another.
 */
#define light_bits_set(mask, bits) \
    (mask | bits)

/**
 * Removes a mask of bits from another.
 */
#define light_bits_clr(mask, bits) \
    (mask & ~bits)

#endif // LIGHT_BASE_BITS_HPP
