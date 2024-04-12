#include <pax/Base/Array2d.hpp>

namespace pax
{
    template <class Item>
    Array2d<Item>
    array2d_create(Item* data, v2u64 size)
    {
        Array2d<Item> value;
        const u64     area = size(0) * size(1);

        if ( data != 0 && area != 0 ) {
            value.data = data;
            value.size = size;
            value.area = area;
        }

        return value;
    }

    template <class Item>
    Array2d<Item>
    array2d_create(v2u64 size)
    {
        Array2d<Item> value;
        const u64     bytes = pax_bytes_of(Item);
        const u64     area  = size(0) * size(1);

        if ( size != v2u64::ZERO ) {
            value.data = (Item*) calloc(area, bytes);
            value.size = size;
            value.area = area;
        }

        return value;
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
