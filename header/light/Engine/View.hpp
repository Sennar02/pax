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
        v2f64 centre;

        /**
         * Size of the view in units.
         */
        v2u64 size;

        /**
         * Unit of size.
         */
        u64 unit;

    public:
        /**
         *
         */
        v2f64
        offset() const;

        /**
         *
         */
        v4u64
        visible(v2u64 limits) const;
    };
} // light

#endif // LIGHT_ENGINE_VIEW_HPP
