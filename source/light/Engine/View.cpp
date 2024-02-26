#include <light/Engine/View.hpp>

namespace light
{
    Vec2f
    View::origin() const
    {
        return centre - size * (unit / 2u);
    }

    Vec4u
    View::visible(Vec2u limits) const
    {
        Vec2u half = size * (unit / 2u);
        Vec2f min  = centre - half;
        Vec2f max  = centre + half;

        Vec4u bounds = {
            (u64) light_max(round_bot(min[0] - unit), 0),
            (u64) light_max(round_top(max[0] + unit), 0),
            (u64) light_max(round_bot(min[1] - unit), 0),
            (u64) light_max(round_top(max[1] + unit), 0),
        };

        bounds[1] = light_min(bounds[1], limits[0] * unit);
        bounds[3] = light_min(bounds[3], limits[1] * unit);

        return bounds / unit;
    }
} // light
