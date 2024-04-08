#include <pax/Base/math.hpp>

namespace pax
{
    s64
    math_top(f64 value)
    {
        s64 reslt = value;

        return reslt +
            (value > reslt);
    }

    s64
    math_bot(f64 value)
    {
        s64 reslt = value;

        return reslt -
            (reslt > value);
    }

    s64
    math_rnd(f64 value)
    {
        s64 sig =
            (value > 0) - (value < 0);

        return value + sig * 0.5;
    }

    f64
    math_abs(f64 value)
    {
        s64 sig =
            (value > 0) - (value < 0);

        return value * sig;
    }

    u64
    math_abs(s64 value)
    {
        s64 sig =
            (value > 0) - (value < 0);

        return value * sig;
    }

    f64
    interp_line(f64 value, f64 other, f64 alpha)
    {
        return value * (1 - alpha) + other * alpha;
    }
} // pax
