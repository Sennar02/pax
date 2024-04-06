#include <pax/Base/List.hpp>
#include <pax/Base/Option.hpp>
#include <pax/Base/macros.hpp>

namespace pax
{
    template <class Item>
    List<Item>
    list_create(Item* data, u64 size)
    {
        List<Item> value;

        if ( data != 0 && size != 0 ) {
            value.data = data;
            value.size = size;
        }

        return value;
    }

    template <class Item>
    List<Item>
    list_create(u64 size)
    {
        List<Item> value;
        u64        bytes = pax_bytes_of(Item);

        if ( size != 0 ) {
            value.data  = (Item*) calloc(size, bytes);
            value.size  = size;
        }

        return value;
    }

    template <class Item>
    bool
    List<Item>::acquire(Item* data, u64 size)
    {
        if ( data != 0 && size != 0 ) {
            this->data  = data;
            this->size  = size;
            this->count = 0;

            return true;
        }

        return false;
    }

    template <class Item>
    bool
    List<Item>::acquire(u64 size)
    {
        u64 bytes = pax_bytes_of(Item);

        if ( size != 0 ) {
            this->data  = (Item*) calloc(size, bytes);
            this->size  = size;
            this->count = 0;

            return true;
        }

        return false;
    }

    template <class Item>
    bool
    List<Item>::release()
    {
        free(data);

        data  = 0;
        size  = 0;
        count = 0;

        return true;
    }

    template <class Item>
    bool
    List<Item>::is_empty() const
    {
        return count == 0;
    }

    template <class Item>
    bool
    List<Item>::is_full() const
    {
        return count == size;
    }

    template <class Item>
    bool
    List<Item>::swap(u64 index, u64 other)
    {
        Item temp = {};

        if ( index < count && other < count ) {
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
    bool
    List<Item>::push(u64 index, s64 displ)
    {
        s64 dir = (displ > 0) - (displ < 0);
        u64 mod = (displ < 0) * (count - index);
        u64 lim = (displ > 0) * (displ) + count;
        u64 src = 0;
        u64 dst = 0;

        if ( count + displ > size ) return false;

        for ( u64 i = 0; i < count + displ - index; i += 1u ) {
            dst = count - (mod + dir * i);
            src = dst - displ;

            if ( dst <= lim && src <= lim )
                data[dst] = data[src];
        }

        count += displ;

        return true;
    }

    template <class Item>
    Option<u64>
    List<Item>::insert(Item item, u64 index)
    {
        u64 other = count;

        if ( index <= other && other < size ) {
            push(other, +1);
            swap(index, other);

            data[index] = item;

            return option_create(index);
        }

        return {};
    }

    template <class Item>
    Option<Item>
    List<Item>::remove(u64 index)
    {
        Option<Item> value;
        u64          other = count - 1u;

        if ( index <= other && other < size ) {
            value = option_create(data[index]);

            swap(index, other);
            push(other, -1);
        }

        return value;
    }

    template <class Item>
    Option<u64>
    List<Item>::insert_push(Item item, u64 index)
    {
        u64 other = count;

        if ( index <= other && other < size ) {
            push(index, +1);

            data[index] = item;

            return option_create(index);
        }

        return {};
    }

    template <class Item>
    Option<Item>
    List<Item>::remove_push(u64 index)
    {
        Option<Item> value;
        u64          other = count - 1u;

        if ( index <= other && other < size ) {
            value = option_create(data[index]);

            push(index, -1);
        }

        return value;
    }

    template <class Item>
    Array<Item>
    List<Item>::as_array()
    {
        return array_create(data, count);
    }

    template <class Item>
    const Array<Item>
    List<Item>::as_array() const
    {
        return array_create(data, count);
    }

    template <class Item>
    Item&
    List<Item>::item(u64 index)
    {
        pax_test_fmt(index < size,
            "bounds", "index = %lu exceedes size = %lu", index, size
        );

        return data[index];
    }

    template <class Item>
    const Item&
    List<Item>::item(u64 index) const
    {
        pax_test_fmt(index < size,
            "bounds", "index = %lu exceedes size = %lu", index, size
        );

        return data[index];
    }

    template <class Item>
    Item&
    List<Item>::operator()(u64 index)
    {
        pax_test_fmt(index < size,
            "bounds", "index = %lu exceedes size = %lu", index, size
        );

        return data[index];
    }

    template <class Item>
    const Item&
    List<Item>::operator()(u64 index) const
    {
        pax_test_fmt(index < size,
            "bounds", "index = %lu exceedes size = %lu", index, size
        );

        return data[index];
    }
} // pax
