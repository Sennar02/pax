#include <light/Engine/View.hpp>

namespace light
{
    v2f64
    View::offset() const
    {
        return centre - size * (unit / 2u);
    }

    v4u64
    View::visible(v2u64 limits) const
    {
        v2u64 half = size * (unit / 2u);
        v2f64 min  = centre - half;
        v2f64 max  = centre + half;

        v4u64 bounds = {
            (u64) light_max(trunc_bot(min[0] - unit), 0),
            (u64) light_max(trunc_top(max[0] + unit), 0),
            (u64) light_max(trunc_bot(min[1] - unit), 0),
            (u64) light_max(trunc_top(max[1] + unit), 0),
        };

        bounds[1] = light_min(bounds[1], limits[0] * unit);
        bounds[3] = light_min(bounds[3], limits[1] * unit);

        return bounds / unit;
    }
} // light
