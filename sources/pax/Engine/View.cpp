#include <pax/Engine/View.hpp>

namespace pax
{
    v4f64
    View::rect() const
    {
        v2f64 centre = target + offset;
        v2f64 scaled = (size / scale) / 2.0;

        return {
            centre(0) - scaled(0), // x1
            centre(1) - scaled(1), // y1
            centre(0) + scaled(0), // x2
            centre(1) + scaled(1), // y2
        };
    }

    v4s64
    View::snap(v4f64 rect) const
    {
        return {
            math_bot(rect(0) - 1), // x1
            math_bot(rect(1) - 1), // y1
            math_top(rect(2) + 1), // x2
            math_top(rect(3) + 1), // y2
        };
    }

    v4u64
    View::cull(v4f64 rect, v4u64 limits) const
    {
        v4s64 cull = snap(rect);

        return {
            pax_max((u64) pax_max(cull(0), 0), limits(0)),
            pax_max((u64) pax_max(cull(1), 0), limits(1)),
            pax_min((u64) pax_max(cull(2), 0), limits(2)),
            pax_min((u64) pax_max(cull(3), 0), limits(3)),
        };
    }
} // pax
