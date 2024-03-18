#ifndef PAX_ENGINE_TILE_GRID_HPP
#define PAX_ENGINE_TILE_GRID_HPP

#include <pax/Engine/define.hpp>

namespace pax
{
    struct Tile_Grid
    {
    public:
        /**
         *
         */
        Array2d<u64> table = Array2d<u64>();

        /**
         *
         */
        virtual void
        operate() = 0;
    };
} // pax

#endif // PAX_ENGINE_TILE_GRID_HPP
