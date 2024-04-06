#ifndef PAX_BASE_MATH_HPP
#define PAX_BASE_MATH_HPP

#include <pax/Base/define.hpp>

namespace pax
{
    /**
     * Truncates the number by discarding the
     * fractional part and adding one.
     *
     * For example:
     *  1) 0.12  will produce 1
     *  2) 7.999 will produce 8
     *  3) -0.34 will produce 0
     */
    s64
    math_top(f64 value);

    /**
     * Truncates the number by discarding the
     * fractional part.
     *
     * For example:
     *  1) 0.12  will produce 0
     *  2) 7.999 will produce 7
     *  3) -0.34 will produce -1
     */
    s64
    math_bot(f64 value);

    /**
     * Truncates the number by rounding the value.
     *
     * For example:
     *  1) 0.12  will produce 0
     *  2) 7.999 will produce 8
     *  3) 3.49  will produce 3
     *  4) 3.50  will produce 4
     *  5) -1.34 will produce -1
     *  6) -1.50 will produce -2
     *  7) -1.99 will produce -2
     */
    s64
    math_rnd(f64 value);

    /**
     * todo: Comment.
     */
    f64
    math_abs(f64 value);

    /**
     * todo: Comment.
     */
    u64
    math_abs(s64 value);

    /**
     * todo: Comment.
     */
    f64
    interp_line(f64 value, f64 other, f64 alpha);

    // /**
    //  * Sets the bits specified in the mask to a particular state.
    //  */
    // u64
    // bits_write(u64 number, u64 mask, u8 state);

    // /**
    //  * Returns the exact values of the bits specified in the mask.
    //  */
    // u64
    // bits_read(u64 mask, u64 bits);

    // /**
    //  * Flips the value of the bits specified in the mask.
    //  */
    // u64
    // bits_flip(u64 number, u64 mask);

    // /**
    //  * Determines if the bits specified in the mask are all active.
    //  */
    // bool
    // bits_test(u64 mask, u64 bits);

    // /**
    //  * todo: Comment.
    //  */
    // bool
    // bits_match(u64 mask, u64 bits);
} // pax

/**
 * todo: Comment.
 */
#define bits_write(value, mask) \
    ((value) | (mask))

/**
 * todo: Comment.
 */
#define bits_clear(value, mask) \
    ((value) & ~(mask))

/**
 * todo: Comment.
 */
#define bits_copy(value, mask, state) \
    ((state) != 0) * bits_write(value, mask) + \
    ((state) == 0) * bits_clear(value, mask)

/**
 * todo: Comment.
 */
#define bits_flip(value, mask) \
    ((value) ^ (mask))

/**
 * todo: Comment.
 */
#define bits_read(value, mask) \
    ((value) & (mask))

/**
 * todo: Comment.
 */
#define bits_test(value, mask) \
    (((value) & (mask)) != 0)

/**
 * Compares two values and chooses the larger one with comparisons.
 */
#define pax_max_cmp(a, b) \
    ((a) <= (b) ? (b) : (a))

/**
 * Compares two values and chooses the larger one without branching.
 */
#define pax_max(a, b) \
    (((a) <= (b)) * (b) + ((b) < (a)) * (a))

/**
 * Compares two values and chooses the smaller one with comparisons.
 */
#define pax_min_cmp(a, b) \
    ((a) <= (b) ? (a) : (b))

/**
 * Compares two values and chooses the smaller on without branching.
 */
#define pax_min(a, b) \
    (((a) <= (b)) * (a) + ((b) < (a)) * (b))

/**
 * Determines if a value is inside a range in
 * the form [a, b).
 *
 * Note: The case a > b is tested.
 */
#define pax_is_in(a, b, v) \
    (((a) <= (b)) && ((v) <= (a)) && ((v) < (b)))

#endif // PAX_BASE_MATH_HPP