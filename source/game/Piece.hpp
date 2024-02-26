#ifndef GAME_PIECE_HPP
#define GAME_PIECE_HPP

#include <light/Engine/import.hpp>

namespace game
{
    using namespace light;

    /**
     * Part of an actor which determines its position
     * in world coordinated.
     */
    using Position = Vec2f;

    /**
     * Part of an actor which changes its position.
     */
    struct Motion {
        /**
         * Movement direction in tile relative
         * coordinates, for example:
         *  a. (+1,  0) means east,
         *  b. (-1, +1) means souht-west.
         *
         * Changes only when the actor is not moving.
         *
         * The values for this vector are meant to
         * be only -1, 0 or +1. I don't know what
         * happens otherwise.
         */
        Vec2f step_value = {};

        /**
         * Movement direction in tile relative
         * coordinate, same as step_value but
         * used to correct possible errors and
         * free to change even during the movement.
         */
        Vec2f step_input = {};

        /**
         * Position in grid coordinates.
         */
        Vec2u tile_origin = {};

        /**
         * Destination in grid coordinates.
         */
        Vec2u tile_finish = {};

        /**
         * Maximum movement speed.
         *
         * The value is meant to be a positive value.
         * I don't know what happens otherwise.
         */
        f64 speed_limit = 0;

        /**
         * Actual movement speed, different from
         * speed_limit since this value is normalized
         * based on the angle and can be used to apply
         * acceleration.
         */
        f64 speed_value = 0;

        /**
         * Flags.
         */
        u64 status = 0;

        /**
         * Definitions of the various status flags.
         */
        enum Status {
            /**
             * Wheter currently moving or not.
             */
            MOVING = 1,

            /**
             * Allows or prevents the movement to begin with.
             */
            MOBILE = 2,
        };
    };

    /**
     * Helper type definition for a motion controls function.
     */
    using Motion_Func = Vec2f(void* self);

    /**
     * The simplest and default function for
     * the motion controls. It always returns
     * a (0, 0) vector.
     */
    Vec2f
    motion_func_empty(void* self);

    /**
     * Part of an actor which controls its evolution
     * during the program execution.
     */
    struct Controls {
        Motion_Func* motion = &motion_func_empty;
    };
}

#endif // GAME_PIECE_HPP
