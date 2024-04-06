#include <pax/Base/Store.hpp>
#include <pax/Base/macros.hpp>

namespace pax
{
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
        pax_test_fmt(index < SIZE,
            "bounds", "index = %lu exceedes size = %lu", index, SIZE
        );

        return data[index];
    }

    template <class Item, u64 Size>
    const Item&
    Store<Item, Size>::operator()(u64 index) const
    {
        pax_test_fmt(index < SIZE,
            "bounds", "index = %lu exceedes size = %lu", index, SIZE
        );

        return data[index];
    }
} // pax