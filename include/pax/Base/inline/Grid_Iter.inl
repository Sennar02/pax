#include <pax/Base/Grid_Iter.hpp>

namespace pax
{
    template <class Item>
    bool
    Grid_Iter_Forw<Item>::has_next() const
    {
        return state < limit;
    }

    template <class Item>
    Item&
    Grid_Iter_Forw<Item>::next()
    {
        u64 value = state;

        state += 1u;

        return array[value];
    }

    template <class Item>
    u64
    Grid_Iter_Forw<Item>::index() const
    {
        return state;
    }

    template <class Item>
    u64
    Grid_Iter_Forw<Item>::col() const
    {
        return state % lines;
    }

    template <class Item>
    u64
    Grid_Iter_Forw<Item>::row() const
    {
        return state / lines;
    }

    template <class Item>
    Item&
    Grid_Iter_Forw<Item>::item() const
    {
        return array[state];
    }

    template <class Item>
    Grid_Iter_Forw<Item>&
    Grid_Iter_Forw<Item>::reset()
    {
        state = 0;

        return pax_self;
    }

    template <class Item>
    bool
    Grid_Iter_Back<Item>::has_next() const
    {
        return state < limit;
    }

    template <class Item>
    Item&
    Grid_Iter_Back<Item>::next()
    {
        u64 value = state;

        state -= 1u;

        return array[value];
    }

    template <class Item>
    u64
    Grid_Iter_Back<Item>::index() const
    {
        return state;
    }

    template <class Item>
    u64
    Grid_Iter_Back<Item>::col() const
    {
        return state % lines;
    }

    template <class Item>
    u64
    Grid_Iter_Back<Item>::row() const
    {
        return state / lines;
    }

    template <class Item>
    Item&
    Grid_Iter_Back<Item>::item() const
    {
        return array[state];
    }

    template <class Item>
    Grid_Iter_Back<Item>&
    Grid_Iter_Back<Item>::reset()
    {
        state = 0;

        return pax_self;
    }
} // pax
