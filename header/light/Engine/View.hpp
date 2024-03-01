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
        v2f64 centre = {};

        /**
         * Size of the view in units.
         */
        v2u64 size = {};

        /**
         * Unit of size.
         */
        f64 unit = 0;

        /**
         *
         */
        f64 factor = 1;

    public:
        /**
         *
         */
        v4f64
        bounds() const;

        /**
         *
         */
        v4s64
        snap(v4f64 bounds) const;

        /**
         *
         */
        v4u64
        cull(v4f64 bounds, v4u64 limits) const;
    };
} // light

#endif // LIGHT_ENGINE_VIEW_HPP
