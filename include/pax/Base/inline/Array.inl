#include <pax/Base/Array.hpp>

namespace pax
{
    template <class Item>
    Array<Item>
    array_create(Item* data, u64 size)
    {
        Array<Item> value;

        if ( data != 0 && size != 0 ) {
            value.data = data;
            value.size = size;
        }

        return value;
    }

    template <class Item>
    Array<Item>
    array_create(u64 size)
    {
        Array<Item> value;
        const u64   bytes = pax_bytes_of(Item);

        if ( size != 0 ) {
            value.data = (Item*) calloc(size, bytes);
            value.size = size;
        }

        return value;
    }

    template <class Item>
    Array<Item>&
    array_shuffle(Array<Item>& array, v2u64 range)
    {
        range = array.clamp(range);

        for ( u64 i = range(1); i > range(0); i -= 1u )
            array.swap(i - 1u, rand() % i);

        return array;
    }

    template <class Item>
    Array<Item>::Array()
    { }

    template <class Item>
    bool
    Array<Item>::acquire(Item* data, u64 size)
    {
        if ( data != 0 && size != 0 ) {
            this->data = data;
            this->size = size;

            return true;
        }

        return false;
    }

    template <class Item>
    bool
    Array<Item>::acquire(u64 size)
    {
        const u64 bytes = pax_bytes_of(Item);

        if ( size != 0 ) {
            this->data = (Item*) calloc(size, bytes);
            this->size = size;

            return true;
        }

        return false;
    }

    template <class Item>
    bool
    Array<Item>::release()
    {
        free(data);

        data = 0;
        size = 0;

        return true;
    }

    template <class Item>
    bool
    Array<Item>::contains(u64 index) const
    {
        return index < size;
    }

    template <class Item>
    bool
    Array<Item>::contains(v2u64 index) const
    {
        return index(0) < size &&
               index(1) < size;
    }

    template <class Item>
    u64
    Array<Item>::clamp(u64 index) const
    {
        return pax_min(index, size);
    }

    template <class Item>
    v2u64
    Array<Item>::clamp(v2u64 index) const
    {
        index(0) = pax_min(index(0), size);
        index(1) = pax_min(index(1), size);

        return index;
    }

    template <class Item>
    bool
    Array<Item>::swap(u64 index, u64 other)
    {
        Item temp = {};

        if ( index < size && other < size ) {
            if ( index != other ) {
                temp = data[index];

                data[index] = data[other];
                data[other] = temp;
            }

            return true;
        }

        return false;
    }

    template <class Item>
    template <class Func>
    Array<Item>&
    Array<Item>::loop(v2u64 range, Func func)
    {
        range = clamp(range);

        for ( u64 i = range(0); i < range(1); i += 1u )
            func(data[i], i);

        return pax_self;
    }

    template <class Item>
    template <class Func>
    const Array<Item>&
    Array<Item>::loop(v2u64 range, Func func) const
    {
        range = clamp(range);

        for ( u64 i = range(0); i < range(1); i += 1u )
            func(data[i], i);

        return pax_self;
    }

    template <class Item>
    Item&
    Array<Item>::item(u64 index)
    {
        pax_test_fmt(index < size,
            "bounds", "index = %lu exceedes size = %lu", index, size
        );

        return data[index];
    }

    template <class Item>
    const Item&
    Array<Item>::item(u64 index) const
    {
        pax_test_fmt(index < size,
            "bounds", "index = %lu exceedes size = %lu", index, size
        );

        return data[index];
    }

    template <class Item>
    Item&
    Array<Item>::operator()(u64 index)
    {
        return item(index);
    }

    template <class Item>
    const Item&
    Array<Item>::operator()(u64 index) const
    {
        return item(index);
    }
} // pax
