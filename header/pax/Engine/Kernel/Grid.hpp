#ifndef PAX_ENGINE_GRID_HPP
#define PAX_ENGINE_GRID_HPP

#include <pax/Engine/define.hpp>
#include <pax/Engine/Kernel/Grid_Layer.hpp>

namespace pax
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
} // pax

#endif // PAX_ENGINE_GRID_HPP
