#include <pax/Engine/View.hpp>

namespace pax
{
    v4f64
    View::bounds() const
    {
        v2f64 centre = target + offset;
        v2f64 scaled = size / scale / 2.0;

        return {
            centre(0) - scaled(0), // x1
            centre(1) - scaled(1), // y1
            centre(0) + scaled(0), // x2
            centre(1) + scaled(1), // y2
        };
    }

    v4s64
    View::snap(v4f64 bounds) const
    {
        return {
            math_bot(bounds(0) - 1), // x1
            math_bot(bounds(1) - 1), // y1
            math_top(bounds(2) + 1), // x2
            math_top(bounds(3) + 1), // y2
        };
    }

    v4u64
    View::cull(v4f64 bounds, v4u64 limits) const
    {
        v4s64 region = snap(bounds);

        return {
            pax_max((u64) pax_max(region(0), 0), limits(0)),
            pax_max((u64) pax_max(region(1), 0), limits(1)),
            pax_min((u64) pax_max(region(2), 0), limits(2)),
            pax_min((u64) pax_max(region(3), 0), limits(3)),
        };
    }
} // pax