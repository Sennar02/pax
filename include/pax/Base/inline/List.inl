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
        const u64  bytes = pax_bytes_of(Item);

        if ( size != 0 ) {
            value.data = (Item*) calloc(size, bytes);
            value.size = size;
        }

        return value;
    }

    template <class Item>
    List<Item>&
    shuffle(List<Item>& list)
    {
        u64  index = 0;
        auto iter  = iter_back_create(list);

        for ( ; iter.has_next(); iter.next() ) {
            index = iter.index();

            swap(list, index,
                rand() % (index + 1u)
            );
        }

        return list;
    }

    template <class Item>
    bool
    swap(List<Item>& list, u64 index, u64 other)
    {
        Item temp = {};

        if ( list.contains(index) == false ||
             list.contains(other) == false
        ) return false;

        if ( index != other ) {
            temp = list(index);

            list(index) = list(other);
            list(other) = temp;
        }

        return true;
    }

    template <class Item>
    Line_Iter_Forw<const Item>
    iter_forw_create(const List<Item>& list)
    {
        Line_Iter_Forw<const Item> iter;

        iter.array = list.data;
        iter.limit = list.count;
        iter.state = 0;

        return iter;
    }

    template <class Item>
    Line_Iter_Forw<Item>
    iter_forw_create(List<Item>& list)
    {
        Line_Iter_Forw<Item> iter;

        iter.array = list.data;
        iter.limit = list.count;
        iter.state = 0;

        return iter;
    }

    template <class Item>
    Line_Iter_Back<const Item>
    iter_back_create(const List<Item>& list)
    {
        Line_Iter_Back<const Item> iter;

        iter.array = list.data;
        iter.limit = list.count;
        iter.state = list.count - 1u;

        return iter;
    }

    template <class Item>
    Line_Iter_Back<Item>
    iter_back_create(List<Item>& list)
    {
        Line_Iter_Back<Item> iter;

        iter.array = list.data;
        iter.limit = list.count;
        iter.state = list.count - 1u;

        return iter;
    }

    template <class Item>
    List<Item>::List()
    { }

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
        const u64 bytes = pax_bytes_of(Item);

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
    List<Item>::contains(u64 index) const
    {
        return index < count;
    }

    template <class Item>
    bool
    List<Item>::slide(u64 index, s64 displ)
    {
        const s64 sign = (displ > 0) - (displ < 0);
        const u64 stop = (displ > 0) * displ + count;

        u64 orig = 1u - displ;
        u64 dest = (displ > 0) * count +
                   (displ < 0) * index + 1u;

        if ( displ + count > size ) return false;

        count += displ;

        for ( u64 i = 0; i < count; i += 1u ) {
            orig -= sign, dest -= sign;

            if ( orig <= stop && dest <= stop )
                data[dest] = data[orig];
        }

        return true;
    }

    template <class Item>
    Option<u64>
    List<Item>::insert(Item item, u64 index)
    {
        const u64 other = count;

        if ( index <= other && other < size ) {
            slide(other, +1);
            swap(pax_self, index, other);

            data[index] = item;

            return option_create(index);
        }

        return {};
    }

    template <class Item>
    Option<u64>
    List<Item>::insert_tail(Item item)
    {
        return insert(item, count);
    }

    template <class Item>
    Option<u64>
    List<Item>::insert_head(Item item)
    {
        return insert(item, 0);
    }

    template <class Item>
    Option<Item>
    List<Item>::remove(u64 index)
    {
        Option<Item> value;
        const u64    other = count - 1u;

        if ( index <= other && other < size ) {
            value = option_create(data[index]);

            swap(pax_self, index, other);
            slide(other, -1);
        }

        return value;
    }

    template <class Item>
    Option<Item>
    List<Item>::remove_tail()
    {
        return remove(count - 1u);
    }

    template <class Item>
    Option<Item>
    List<Item>::remove_head()
    {
        return remove(0);
    }

    template <class Item>
    List<Item>&
    List<Item>::clear()
    {
        count = 0;

        return pax_self;
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
        return item(index);
    }

    template <class Item>
    const Item&
    List<Item>::operator()(u64 index) const
    {
        return item(index);
    }
} // pax
