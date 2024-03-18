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
    top(f64 value);

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
    bot(f64 value);

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
    rnd(f64 value);
} // pax

/**
 * Compares two values and chooses the larger one.
 */
#define pax_max(a, b) \
    ((a) < (b) ? (b) : (a))

/**
 * Compares two values and chooses the larger one without branching.
 */
#define pax_max_bl(a, b) \
    (((a) <= (b)) * (b) + ((b) < (a)) * (a))

/**
 * Compares two values and chooses the smaller one.
 */
#define pax_min(a, b) \
    ((a) < (b) ? (a) : (b))

/**
 * Compares two values and chooses the smaller on without branching.
 */
#define pax_min_bl(a, b) \
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
