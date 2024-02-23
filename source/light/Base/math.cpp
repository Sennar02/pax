#include <light/Base/math.hpp>

namespace light
{
    s64
    round_top(f64 val)
    {
        s64 res = val;

        if ( res < val )
            return res + 1;

        return res;
    }

    s64
    round_bot(f64 val)
    {
        s64 res = val;

        if ( res > val )
            return res - 1;

        return res;
    }

    s64
    round(f64 val)
    {
        return val + 0.5;
    }
} // light
