#include <pax/Signal/Dispatcher.hpp>

namespace pax
{
    struct Dispatcher::Holder {
        void* func;
        void* ctxt;
    };

    template <class Item>
    Option<u64>
    Dispatcher::insert(void (*func) (Item))
    {

        u64 type = Item::SIGNAL_TYPE;

        if ( func != 0 && type < table.count ) {
            List<Holder>& list = table(type);

            return list.insert(
                {(void*) func, (void*) 0}, list.count
            );
        }

        return {};
    }

    template <class Item, class Ctxt>
    Option<u64>
    Dispatcher::insert(void (*func) (Item, Ctxt*), Ctxt& ctxt)
    {

        u64 type = Item::SIGNAL_TYPE;

        if ( func != 0 && type < table.count ) {
            List<Holder>& list = table(type);

            return list.insert(
                {(void*) func, (void*) &ctxt}, list.count
            );
        }

        return {};
    }

    template <class Item>
    Option<void*>
    Dispatcher::remove(u64 index)
    {
        u64 type = Item::SIGNAL_TYPE;

        if ( type < table.count ) {
            Option<Holder> value = table(type).remove(index);

            if ( value.valid )
                return option_create(value.item.func);
        }

        return {};
    }

    template <class Item>
    bool
    Dispatcher::publish(Item payload) const
    {
        u64    type = Item::SIGNAL_TYPE;
        Holder iter = {};

        if ( type < table.count ) {
            const List<Holder>& list = table(type);

            for ( u64 i = 0; i < list.count; i += 1u ) {
                iter = list(i);

                if ( iter.ctxt != 0 )
                    ((void (*) (Item, void*)) iter.func)(payload, iter.ctxt);
                else
                    ((void (*) (Item)) iter.func)(payload);
            }

            return list.count != 0;
        }

        return false;
    }
} // pax