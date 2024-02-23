#ifndef LIGHT_BASE_MATH_HPP
#define LIGHT_BASE_MATH_HPP

#include <light/Base/define.hpp>

namespace light
{
    s64
    round_top(f64 val);

    s64
    round_bot(f64 val);

    s64
    round(f64 val);
} // light

/**
 * Compares two values and chooses the bigger one.
 */
#define light_max(a, b) \
    (a < b ? b : a)

/**
 * Compares two values and chooses the smaller one.
 */
#define light_min(a, b) \
    (a < b ? a : b)

/**
 * Determines if a value is inside a range. The
 * range is assumed to be in the form [a, b].
 *
 * Note: The case a > b is tested.
 */
#define light_is_in(a, b, v) \
    (a <= b && a <= v && v <= b)

/**
 * Confines a value within a range. The range
 * is assumed to be in the form [a, b].
 */
#define light_clamp(a, b, v) \
    light_min(b, light_max(a, v))

#endif // LIGHT_BASE_MATH_HPP
