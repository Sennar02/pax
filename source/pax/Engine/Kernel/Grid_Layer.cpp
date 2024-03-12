#include <pax/Engine/Kernel/Grid_Layer.hpp>

namespace pax
{
    bool
    Grid_Layer::push(Grid_Step* step)
    {
        u64 index = count + 1u;

        if ( step == 0 ) return false;

        if ( count < steps.size ) {
            steps[count] = step;
            count        = index;
        }

        return count == index;
    }

    Grid_Step*
    Grid_Layer::pull()
    {
        Grid_Step* res   = 0;
        u64        index = count - 1u;

        if ( count != 0 ) {
            count = index;
            res   = steps[count];
        }

        return res;
    }
} // pax
