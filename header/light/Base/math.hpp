#ifndef LIGHT_BASE_MATH_HPP
#define LIGHT_BASE_MATH_HPP

#include <light/Base/define.hpp>

namespace light
{
    /**
     * Truncates the number by discarding the
     * fractional part and adding one.
     *
     * For example:
     *  1) 0.12  will produce 1
     *  2) 7.999 will produce 8
     */
    s64
    trunc_top(f64 val);

    /**
     * Truncates the number by discarding the
     * fractional part.
     *
     * For example:
     *  1) 0.12  will produce 0
     *  2) 7.999 will produce 7
     */
    s64
    trunc_bot(f64 val);

    /**
     * Truncates the number by rounding the value.
     *
     * For example:
     *  1) 0.12  will produce 0
     *  2) 7.999 will produce 8
     *  3) 3.49  will produce 3
     *  4) 3.50  will produce 4
     */
    s64
    trunc_rnd(f64 val);
} // light

/**
 * Compares two values and chooses the larger one.
 */
#define light_max(a, b) \
    (a < b ? b : a)

/**
 * Compares two values and chooses the smaller one.
 */
#define light_min(a, b) \
    (a < b ? a : b)

/**
 * Determines if a value is inside a range in
 * the form [a, b).
 *
 * Note: The case a > b is tested.
 */
#define light_is_in(a, b, v) \
    (a <= b && a <= v && v < b)

#endif // LIGHT_BASE_MATH_HPP
