#ifndef LIGHT_ENGINE_GRID_HPP
#define LIGHT_ENGINE_GRID_HPP

#include <light/Engine/define.hpp>
#include <light/Engine/Kernel/Grid_Layer.hpp>

namespace light
{
    struct Grid
    {
    public:
        /**
         *
         */
        Array<Grid_Layer> layers = Array<Grid_Layer>();

        /**
         *
         */
        u64 count = 0;

    public:
        /**
         *
         */
        bool
        push(Grid_Layer layer);

        /**
         *
         */
        Grid_Layer
        pull();
    };
} // light

#endif // LIGHT_ENGINE_GRID_HPP
