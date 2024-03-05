#ifndef LIGHT_ENGINE_GRID_LAYER_HPP
#define LIGHT_ENGINE_GRID_LAYER_HPP

#include <light/Engine/define.hpp>

namespace light
{
    /**
     *
     */
    struct Grid_Step
    {
    public:
        /**
         *
         */
        virtual void
        fixed_step(f64, Array2d<u64>&) {}

        /**
         *
         */
        virtual void
        after_step(Array2d<u64>&) {}
    };

    struct Grid_Layer
    {
    public:
        /**
         *
         */
        Array2d<u64> table = Array2d<u64>();

        /**
         *
         */
        Array<Grid_Step*> steps =
            Array<Grid_Step*>();

        /**
         *
         */
        u64 count = 0;

    public:
        /**
         *
         */
        bool
        push(Grid_Step* step);

        /**
         *
         */
        Grid_Step*
        pull();
    };
} // light

#endif // LIGHT_ENGINE_GRID_LAYER_HPP
