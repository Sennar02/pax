#include <pax/Base/Array2d.hpp>

namespace pax
{
    template <class Item>
    Array2d<Item>
    array2d_create(Item* data, u64 cols, u64 rows)
    {
        Array2d<Item> value;
        const u64     area = cols * rows;

        if ( data != 0 && area != 0 ) {
            value.data = data;
            value.area = area;
            value.size = {cols, rows};
        }

        return value;
    }

    template <class Item>
    Array2d<Item>
    array2d_create(Item* data, v2u64 size)
    {
        return array2d_create<Item>(data, size(0), size(1));
    }

    template <class Item>
    Array2d<Item>
    array2d_create(u64 cols, u64 rows)
    {
        Array2d<Item> value;
        const u64     bytes = pax_bytes_of(Item);
        const u64     area  = cols * rows;

        if ( area != 0 ) {
            value.data = (Item*) calloc(area, bytes);
            value.area = area;
            value.size = {cols, rows};
        }

        return value;
    }

    template <class Item>
    Array2d<Item>
    array2d_create(v2u64 size)
    {
        return array2d_create<Item>(size(0), size(1));
    }

    template <class Item>
    Array2d<Item>&
    shuffle(Array2d<Item>& array)
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
    swap(Array2d<Item>& array, u64 index, u64 other)
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
    bool
    swap(Array2d<Item>& array, u64 col_1, u64 row_1, u64 col_2, u64 row_2)
    {
        Item  temp  = {};
        v2u64 index = {col_1, row_1};
        v2u64 other = {col_2, row_2};

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
    bool
    swap(Array2d<Item>& array, v2u64 index, v2u64 other)
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
    Grid_Iter_Forw<const Item>
    iter_forw_create(const Array2d<Item>& array)
    {
        Grid_Iter_Forw<const Item> iter;

        iter.array = array.data;
        iter.limit = array.area;
        iter.lines = array.size(0);
        iter.state = 0;

        return iter;
    }

    template <class Item>
    Grid_Iter_Forw<Item>
    iter_forw_create(Array2d<Item>& array)
    {
        Grid_Iter_Forw<Item> iter;

        iter.array = array.data;
        iter.limit = array.area;
        iter.lines = array.size(0);
        iter.state = 0;

        return iter;
    }

    template <class Item>
    Grid_Iter_Back<const Item>
    iter_back_create(const Array2d<Item>& array)
    {
        Grid_Iter_Back<const Item> iter;

        iter.array = array.data;
        iter.limit = array.area;
        iter.lines = array.size(0);
        iter.state = array.area - 1u;

        return iter;
    }

    template <class Item>
    Grid_Iter_Back<Item>
    iter_back_create(Array2d<Item>& array)
    {
        Grid_Iter_Back<Item> iter;

        iter.array = array.data;
        iter.limit = array.area;
        iter.lines = array.size(0);
        iter.state = array.area - 1u;

        return iter;
    }

    template <class Item>
    Array2d<Item>::Array2d()
    { }

    template <class Item>
    bool
    Array2d<Item>::acquire(Item* data, v2u64 size)
    {
        const u64 area = size(0) * size(1);

        if ( data != 0 && size != v2u64::ZERO ) {
            this->data = data;
            this->size = size;
            this->area = area;

            return true;
        }

        return false;
    }

    template <class Item>
    bool
    Array2d<Item>::acquire(v2u64 size)
    {
        const u64 bytes = pax_bytes_of(Item);
        const u64 area  = size(0) * size(1);

        if ( size != v2u64::ZERO ) {
            this->data = (Item*) calloc(area, bytes);
            this->size = size;
            this->area = area;

            return true;
        }

        return false;
    }

    template <class Item>
    bool
    Array2d<Item>::release()
    {
        free(data);

        data = 0;
        size = {};
        area = 0;

        return true;
    }

    template <class Item>
    bool
    Array2d<Item>::contains(u64 index) const
    {
        return index < area;
    }

    template <class Item>
    bool
    Array2d<Item>::contains(u64 col, u64 row) const
    {
        return col < size(0) &&
               row < size(1);
    }

    template <class Item>
    bool
    Array2d<Item>::contains(v2u64 index) const
    {
        return contains(index(0), index(1));
    }

    template <class Item>
    Array<Item>
    Array2d<Item>::as_array()
    {
        return array_create(data, area);
    }

    template <class Item>
    const Array<Item>
    Array2d<Item>::as_array() const
    {
        return array_create(data, area);
    }

    template <class Item>
    Array<Item>
    Array2d<Item>::line(u64 index)
    {
        pax_test_fmt(index < size(1),
            "bounds", "index = %lu exceedes size = %lu", index, size(1)
        );

        return array_create(data + index * size(0), size(0));
    }

    template <class Item>
    const Array<Item>
    Array2d<Item>::line(u64 index) const
    {
        pax_test_fmt(index < size(1),
            "bounds", "index = %lu exceedes size = %lu", index, size(1)
        );

        return array_create(data + index * size(0), size(0));
    }

    template <class Item>
    Item&
    Array2d<Item>::item(u64 index)
    {
        pax_test_fmt(index < area,
            "bounds", "index = %lu exceedes size = %lu", index, area
        );

        return data[index];
    }

    template <class Item>
    const Item&
    Array2d<Item>::item(u64 index) const
    {
        pax_test_fmt(index < area,
            "bounds", "index = %lu exceedes size = %lu", index, area
        );

        return data[index];
    }

    template <class Item>
    Item&
    Array2d<Item>::item(u64 col, u64 row)
    {
        pax_test_fmt(col < size(0),
            "bounds", "index = %lu exceedes size = %lu", col, size(0)
        );

        pax_test_fmt(row < size(1),
            "bounds", "index = %lu exceedes size = %lu", row, size(1)
        );

        return data[col + size(0) * row];
    }

    template <class Item>
    const Item&
    Array2d<Item>::item(u64 col, u64 row) const
    {
        pax_test_fmt(col < size(0),
            "bounds", "index = %lu exceedes size = %lu", col, size(0)
        );

        pax_test_fmt(row < size(1),
            "bounds", "index = %lu exceedes size = %lu", row, size(1)
        );

        return data[col + size(0) * row];
    }

    template <class Item>
    Item&
    Array2d<Item>::item(v2u64 index)
    {
        return item(index(0), index(1));
    }

    template <class Item>
    const Item&
    Array2d<Item>::item(v2u64 index) const
    {
        return item(index(0), index(1));
    }

    template <class Item>
    Array<Item>
    Array2d<Item>::operator[](u64 index)
    {
        return line(index);
    }

    template <class Item>
    const Array<Item>
    Array2d<Item>::operator[](u64 index) const
    {
        return line(index);
    }

    template <class Item>
    Item&
    Array2d<Item>::operator()(u64 index)
    {
        return item(index);
    }

    template <class Item>
    const Item&
    Array2d<Item>::operator()(u64 index) const
    {
        return item(index);
    }

    template <class Item>
    Item&
    Array2d<Item>::operator()(u64 col, u64 row)
    {
        return item(col, row);
    }

    template <class Item>
    const Item&
    Array2d<Item>::operator()(u64 col, u64 row) const
    {
        return item(col, row);
    }

    template <class Item>
    Item&
    Array2d<Item>::operator()(v2u64 index)
    {
        return item(index);
    }

    template <class Item>
    const Item&
    Array2d<Item>::operator()(v2u64 index) const
    {
        return item(index);
    }
} // pax
