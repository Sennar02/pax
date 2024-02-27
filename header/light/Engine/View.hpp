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
        u64 unit;

    public:
        /**
         *
         */
        Vec2f
        offset() const;

        /**
         *
         */
        Vec4u
        visible(Vec2u limits) const;
    };
} // light

#endif // LIGHT_ENGINE_VIEW_HPP
