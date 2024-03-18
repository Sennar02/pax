#include <pax/Signal/Dispatcher.hpp>

namespace pax
{
    Dispatcher
    Dispatcher::build(v2u64 size, Alloc* alloc)
    {
        Dispatcher reslt;

        if ( reslt.table.create(size[1], alloc) ) {
            for ( u64 i = 0; i < reslt.table.size; i += 1u )
                reslt.table[i].create(size[0], alloc);
        }

        return reslt;
    }
} // pax