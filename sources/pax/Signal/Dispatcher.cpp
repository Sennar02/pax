#include <pax/Signal/Dispatcher.hpp>

namespace pax
{
    Dispatcher::Dispatcher()
    { }

    bool
    Dispatcher::acquire(v2u64 size)
    {
        List<Invoked> list = {};

        if ( table.acquire(size(0)) == false )
            return false;

        for ( u64 i = 0; i < table.size; i += 1u ) {
            list = list_create<Invoked>(size(1));

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
