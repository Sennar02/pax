#include <pax/Signal/Dispatcher.hpp>

namespace pax
{
    template <class Item>
    Option<u64>
    Dispatcher::insert(Invoker<void(Item)> invoker)
    {
        List<Invoked>* list = 0;
        const u64      type = Item::SIGNAL_TYPE;

        if ( invoker.is_valid() && type < table.count ) {
            list = &table(type);

            return list->insert(
                {invoker.func, invoker.ctxt}, list->count
            );
        }

        return {};
    }

    template <class Item>
    Option<Invoked>
    Dispatcher::remove(u64 index)
    {
        const u64 type = Item::SIGNAL_TYPE;

        if ( type < table.count )
            return table(type).remove(index);

        return {};
    }

    template <class Item>
    bool
    Dispatcher::publish(Item payload) const
    {
        const List<Invoked>* list = 0;
        const u64            type = Item::SIGNAL_TYPE;

        if ( type < table.count ) {
            list = &table(type);

            for ( u64 i = 0; i < list->count; i += 1u )
                invoke<void, Item>(list->item(i), payload);

            return list->count != 0;
        }

        return false;
    }
} // pax
