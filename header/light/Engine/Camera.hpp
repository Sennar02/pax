#ifndef LIGHT_ENGINE_CAMERA_HPP
#define LIGHT_ENGINE_CAMERA_HPP

#include <light/Engine/define.hpp>

namespace light
{
    struct Camera
    {
    public:
        /**
         * Where the center of the camera
         * looks in the world.
         */
        Vec2f center;

        /**
         * Distance from the center.
         */
        Vec2f offset;

    public:
        /**
         *
         */
        Vec2f
        top_left() const;

        /**
         *
         */
        Vec2f
        bot_right() const;

        /**
         *
         */
        Vec4u
        bounds(u32 tile, Vec2u area) const;
    };

    Vec2f
    Camera::top_left() const
    {
        return center - offset;
    }

    Vec2f
    Camera::bot_right() const
    {
        return center + offset;
    }

    Vec4u
    Camera::bounds(u32 tile, Vec2u area) const
    {
        Vec2f tl = top_left();
        Vec2f br = bot_right();

        return {
            (u32) light_max(floor(tl[0] / tile) - 1.f, 0),
            (u32) light_min(ceil(br[0] / tile) + 1.f, (f32) area[0]),
            (u32) light_max(floor(tl[1] / tile) - 1.f, 0),
            (u32) light_min(ceil(br[1] / tile) + 1.f, (f32) area[1]),
        };
    }
} // light

#endif // LIGHT_ENGINE_CAMERA_HPP
