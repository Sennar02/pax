#ifndef PAX_ENGINE_VIEW_HPP
#define PAX_ENGINE_VIEW_HPP

#include <pax/Engine/define.hpp>

namespace pax
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
        u64 unit = 1;

        /**
         *
         */
        v2f64 offset = {};

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
} // pax

#endif // PAX_ENGINE_VIEW_HPP
