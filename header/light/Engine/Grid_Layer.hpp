#ifndef LIGHT_ENGINE_GRID_LAYER_HPP
#define LIGHT_ENGINE_GRID_LAYER_HPP

#include <light/Engine/define.hpp>

namespace light
{
    /**
     *
     */
    using Grid_Action =
        void(Array2d<u64>& tiles, void* extra);

    struct Grid_Layer
    {
    public:
        /**
         *
         */
        Array2d<u64> indeces = Array2d<u64>();

        /**
         *
         */
        Array<Grid_Action*> actions =
            Array<Grid_Action*>();

        /**
         *
         */
        u64 count = 0;

    public:
        /**
         *
         */
        bool
        push(Grid_Action* action);

        /**
         *
         */
        Grid_Action*
        pull();
    };
} // light

#endif // LIGHT_ENGINE_GRID_LAYER_HPP
