#include <pax/Base/Store.hpp>
#include <pax/Base/macros.hpp>

namespace pax
{
    template <class Item, u64 Size>
    Store<Item, Size>&
    store_shuffle(Store<Item, Size>& store, v2u64 range)
    {
        range = store.clamp(range);

        for ( u64 i = range(1); i > range(0); i -= 1u )
            store.swap(i - 1u, rand() % i);

        return store;
    }

    template <class Item, u64 Size>
    bool
    Store<Item, Size>::contains(u64 index) const
    {
        return index < SIZE;
    }

    template <class Item, u64 Size>
    bool
    Store<Item, Size>::contains(v2u64 index) const
    {
        return index(0) < SIZE &&
               index(1) < SIZE;
    }

    template <class Item, u64 Size>
    u64
    Store<Item, Size>::clamp(u64 index) const
    {
        return pax_min(index, SIZE);
    }

    template <class Item, u64 Size>
    v2u64
    Store<Item, Size>::clamp(v2u64 index) const
    {
        index(0) = pax_min(index(0), SIZE);
        index(1) = pax_min(index(1), SIZE);

        return index;
    }

    template <class Item, u64 Size>
    bool
    Store<Item, Size>::swap(u64 index, u64 other)
    {
        Item temp = {};

        if ( index < SIZE && other < SIZE ) {
            if ( index != other ) {
                temp = data[index];

                data[index] = data[other];
                data[other] = temp;
            }

            return true;
        }

        return false;
    }

    template <class Item, u64 Size>
    template <class Func>
    Store<Item, Size>&
    Store<Item, Size>::loop(v2u64 range, Func func)
    {
        range = clamp(range);

        for ( u64 i = range(0); i < range(1); i += 1u )
            func(data[i], i);

        return pax_self;
    }

    template <class Item, u64 Size>
    template <class Func>
    const Store<Item, Size>&
    Store<Item, Size>::loop(v2u64 range, Func func) const
    {
        range = clamp(range);

        for ( u64 i = range(0); i < range(1); i += 1u )
            func(data[i], i);

        return pax_self;
    }

    template <class Item, u64 Size>
    Item&
    Store<Item, Size>::item(u64 index)
    {
        pax_test_fmt(index < SIZE,
            "bounds", "index = %lu exceedes size = %lu", index, SIZE
        );

        return data[index];
    }

    template <class Item, u64 Size>
    const Item&
    Store<Item, Size>::item(u64 index) const
    {
        pax_test_fmt(index < SIZE,
            "bounds", "index = %lu exceedes size = %lu", index, SIZE
        );

        return data[index];
    }

    template <class Item, u64 Size>
    Item&
    Store<Item, Size>::operator()(u64 index)
    {
        return item(index);
    }

    template <class Item, u64 Size>
    const Item&
    Store<Item, Size>::operator()(u64 index) const
    {
        return item(index);
    }
} // pax
