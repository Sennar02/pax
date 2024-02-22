#ifndef LIGHT_ENGINE_VIEW_HPP
#define LIGHT_ENGINE_VIEW_HPP

#include <light/Engine/define.hpp>

namespace light
{
    struct View
    {
    public:
        /**
         * Where the view looks in the world
         * in world coordinates.
         */
        Vec2f centre;

        /**
         * Size of the view in units.
         */
        Vec2u size;

        /**
         * Unit of size.
         */
        u32 unit;

    public:
        /**
         *
         */
        Vec2f origin() const;

        /**
         *
         */
        Vec4u
        visible(Vec2u limits) const;
    };

    Vec2f
    View::origin() const
    {
        return centre - (size * unit) / 2u;
    }

    Vec4u
    View::visible(Vec2u limits) const
    {
        Vec2f min = centre - (size + 0) * unit / 2u;
        Vec2f max = centre + (size + 2) * unit / 2u;

        limits *= unit;

        Vec4u bounds = {
            (u32) light_max((s32) min[0], 0),
            light_min((u32) light_max(max[0], 0), limits[0]),
            (u32) light_max((s32) min[1], 0),
            light_min((u32) light_max(max[1], 0), limits[1]),
        };

        return bounds / unit;
    }
} // light

#endif // LIGHT_ENGINE_VIEW_HPP
