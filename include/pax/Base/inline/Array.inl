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
        u64         bytes = pax_bytes_of(Item);

        if ( size != 0 ) {
            value.data = (Item*) calloc(size, bytes);
            value.size = size;
        }

        return value;
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
        u64 bytes = pax_bytes_of(Item);

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
        pax_test_fmt(index < size,
            "bounds", "index = %lu exceedes size = %lu", index, size
        );

        return data[index];
    }

    template <class Item>
    const Item&
    Array<Item>::operator()(u64 index) const
    {
        pax_test_fmt(index < size,
            "bounds", "index = %lu exceedes size = %lu", index, size
        );

        return data[index];
    }
} // pax
