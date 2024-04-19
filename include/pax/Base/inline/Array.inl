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
    shuffle(Array<Item>& array)
    {
        u64  index = 0;
        auto iter  = iter_back_create(array);

        for ( ; iter.has_next(); iter.next() ) {
            index = iter.index();

            swap(array, index,
                rand() % (index + 1u)
            );
        }

        return array;
    }

    template <class Item>
    bool
    swap(Array<Item>& array, u64 index, u64 other)
    {
        Item temp = {};

        if ( array.contains(index) == false ||
             array.contains(other) == false
        ) return false;

        if ( index != other ) {
            temp = array(index);

            array(index) = array(other);
            array(other) = temp;
        }

        return true;
    }

    template <class Item>
    Line_Iter_Forw<const Item>
    iter_forw_create(const Array<Item>& array)
    {
        Line_Iter_Forw<const Item> iter;

        iter.array = array.data;
        iter.limit = array.size;
        iter.state = 0;

        return iter;
    }

    template <class Item>
    Line_Iter_Forw<Item>
    iter_forw_create(Array<Item>& array)
    {
        Line_Iter_Forw<Item> iter;

        iter.array = array.data;
        iter.limit = array.size;
        iter.state = 0;

        return iter;
    }

    template <class Item>
    Line_Iter_Back<const Item>
    iter_back_create(const Array<Item>& array)
    {
        Line_Iter_Back<const Item> iter;

        iter.array = array.data;
        iter.limit = array.size;
        iter.state = array.size - 1u;

        return iter;
    }

    template <class Item>
    Line_Iter_Back<Item>
    iter_back_create(Array<Item>& array)
    {
        Line_Iter_Back<Item> iter;

        iter.array = array.data;
        iter.limit = array.size;
        iter.state = array.size - 1u;

        return iter;
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
