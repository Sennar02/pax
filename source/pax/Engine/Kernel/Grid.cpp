#include <pax/Engine/Kernel/Grid.hpp>

namespace pax
{
    bool
    Grid::push(Grid_Layer layer)
    {
        u64 index = count + 1u;

        if ( count < layers.size ) {
            layers[count] = layer;
            count         = index;
        }

        return count == index;
    }

    Grid_Layer
    Grid::pull()
    {
        Grid_Layer res;
        u32        index = count - 1u;

        if ( count != 0 ) {
            count = index;
            res   = layers[count];
        }

        return res;
    }
} // pax
