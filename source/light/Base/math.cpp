#include <light/Base/math.hpp>

namespace light
{
    s64
    trunc_top(f64 val)
    {
        s64 res = val;

        if ( res < val )
            return res + 1;

        return res;
    }

    s64
    trunc_bot(f64 val)
    {
        s64 res = val;

        if ( res > val )
            return res - 1;

        return res;
    }

    s64
    trunc(f64 val)
    {
        return val + 0.5;
    }
} // light
