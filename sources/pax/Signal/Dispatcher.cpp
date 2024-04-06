#include <pax/Signal/Dispatcher.hpp>

namespace pax
{
    bool
    Dispatcher::acquire(v2u64 size)
    {
        List<Holder> list = {};

        if ( table.acquire(size(0)) == false )
            return false;

        for ( u64 i = 0; i < table.size; i += 1u ) {
            list = list_create<Holder>(size(1));

            table.insert(
                list, table.count
            );
        }

        return true;
    }

    bool
    Dispatcher::release()
    {
        for ( u64 i = 0; i < table.count; i += 1u )
            table(i).release();

        return table.release();
    }
} // pax