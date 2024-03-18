#include <pax/Base/math.hpp>

namespace pax
{
    s64
    top(f64 value)
    {
        s64 reslt = value;

        return reslt +
            (value > reslt);
    }

    s64
    bot(f64 value)
    {
        s64 reslt = value;

        return reslt -
            (reslt > value);
    }

    s64
    rnd(f64 value)
    {
        s64 sig =
            (value > 0) - (value < 0);

        return value + sig * 0.5;
    }
} // pax
