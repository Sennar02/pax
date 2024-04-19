#include <pax/Base/Storage.hpp>
#include <pax/Base/macros.hpp>

namespace pax
{
    template <class Item, u64 Size>
    Storage<Item, Size>&
    shuffle(Storage<Item, Size>& storage)
    {
        u64  index = 0;
        auto iter  = iter_back_create(storage);

        for ( ; iter.has_next(); iter.next() ) {
            index = iter.index();

            swap(storage, index,
                rand() % (index + 1u)
            );
        }

        return storage;
    }

    template <class Item, u64 Size>
    bool
    swap(Storage<Item, Size>& storage, u64 index, u64 other)
    {
        Item temp = {};

        if ( storage.contains(index) == false ||
             storage.contains(other) == false
        ) return false;

        if ( index != other ) {
            temp = storage(index);

            storage(index) = storage(other);
            storage(other) = temp;
        }

        return true;
    }

    template <class Item, u64 Size>
    Line_Iter_Forw<const Item>
    iter_forw_create(const Storage<Item, Size>& storage)
    {
        Line_Iter_Forw<const Item> iter;

        iter.array = storage.data;
        iter.limit = storage.SIZE;
        iter.state = 0;

        return iter;
    }

    template <class Item, u64 Size>
    Line_Iter_Forw<Item>
    iter_forw_create(Storage<Item, Size>& storage)
    {
        Line_Iter_Forw<Item> iter;

        iter.array = storage.data;
        iter.limit = storage.SIZE;
        iter.state = 0;

        return iter;
    }

    template <class Item, u64 Size>
    Line_Iter_Back<const Item>
    iter_back_create(const Storage<Item, Size>& storage)
    {
        Line_Iter_Back<const Item> iter;

        iter.array = storage.data;
        iter.limit = storage.SIZE;
        iter.state = storage.SIZE - 1u;

        return iter;
    }

    template <class Item, u64 Size>
    Line_Iter_Back<Item>
    iter_back_create(Storage<Item, Size>& storage)
    {
        Line_Iter_Back<Item> iter;

        iter.array = storage.data;
        iter.limit = storage.SIZE;
        iter.state = storage.SIZE - 1u;

        return iter;
    }

    template <class Item, u64 Size>
    bool
    Storage<Item, Size>::contains(u64 index) const
    {
        return index < SIZE;
    }

    template <class Item, u64 Size>
    Item&
    Storage<Item, Size>::item(u64 index)
    {
        pax_test_fmt(index < SIZE,
            "bounds", "index = %lu exceedes size = %lu", index, SIZE
        );

        return data[index];
    }

    template <class Item, u64 Size>
    const Item&
    Storage<Item, Size>::item(u64 index) const
    {
        pax_test_fmt(index < SIZE,
            "bounds", "index = %lu exceedes size = %lu", index, SIZE
        );

        return data[index];
    }

    template <class Item, u64 Size>
    Item&
    Storage<Item, Size>::operator()(u64 index)
    {
        return item(index);
    }

    template <class Item, u64 Size>
    const Item&
    Storage<Item, Size>::operator()(u64 index) const
    {
        return item(index);
    }
} // pax
