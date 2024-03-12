#include <pax/Base/math.hpp>

namespace pax
{
    s64
    top(f64 val)
    {
        s64 res = val;

        return res +
            (val > res);
    }

    s64
    bot(f64 val)
    {
        s64 res = val;

        return res -
            (res > val);
    }

    s64
    rnd(f64 val)
    {
        s64 sig =
            (val > 0) - (val < 0);

        return val + sig * 0.5;
    }
} // pax
