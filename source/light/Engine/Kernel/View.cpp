#include <light/Engine/Kernel/View.hpp>

namespace light
{
    v4f64
    View::bounds() const
    {
        f64   fact = unit / (factor * 2u);
        v2f64 orig = centre + offset - size * fact;
        v2f64 stop = centre + offset + size * fact;

        return {
            orig[0], orig[1],
            stop[0], stop[1],
        };
    }

    v4s64
    View::snap(v4f64 bounds) const
    {
        bounds /= unit;

        return {
            bot(bounds[0] - 1),
            bot(bounds[1] - 1),
            top(bounds[2] + 1),
            top(bounds[3] + 1),
        };
    }

    v4u64
    View::cull(v4f64 bounds, v4u64 limits) const
    {
        v4s64 truncs = snap(bounds);

        return {
            light_max(limits[0], (u64) light_max(0, truncs[0])),
            light_max(limits[1], (u64) light_max(0, truncs[1])),
            light_min(limits[2], (u64) light_max(0, truncs[2])),
            light_min(limits[3], (u64) light_max(0, truncs[3])),
        };
    }
} // light
