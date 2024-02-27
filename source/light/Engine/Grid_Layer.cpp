#include <light/Engine/Grid_Layer.hpp>

namespace light
{
    bool
    Grid_Layer::push(Grid_Action* action)
    {
        u64 index = count + 1u;

        if ( action == 0 ) return false;

        if ( count < actions.size ) {
            actions[count] = action;
            count          = index;
        }

        return count == index;
    }

    Grid_Action*
    Grid_Layer::pull()
    {
        Grid_Action* res   = 0;
        u64          index = count - 1u;

        if ( count != 0 ) {
            count = index;
            res   = actions[count];
        }

        return res;
    }
} // light
