#include <pax/Base/Line_Iter.hpp>

namespace pax
{
    template <class Item>
    bool
    Line_Iter_Forw<Item>::has_next() const
    {
        return state < limit;
    }

    template <class Item>
    Item&
    Line_Iter_Forw<Item>::next()
    {
        u64 index = state;

        state += 1u;

        return array[index];
    }

    template <class Item>
    u64
    Line_Iter_Forw<Item>::index() const
    {
        return state;
    }

    template <class Item>
    Item&
    Line_Iter_Forw<Item>::item() const
    {
        return array[state];
    }

    template <class Item>
    Line_Iter_Forw<Item>&
    Line_Iter_Forw<Item>::reset()
    {
        state = 0;

        return pax_self;
    }

    template <class Item>
    bool
    Line_Iter_Back<Item>::has_next() const
    {
        return state < limit;
    }

    template <class Item>
    Item&
    Line_Iter_Back<Item>::next()
    {
        u64 index = state;

        state -= 1u;

        return array[index];
    }

    template <class Item>
    u64
    Line_Iter_Back<Item>::index() const
    {
        return state;
    }

    template <class Item>
    Item&
    Line_Iter_Back<Item>::item() const
    {
        return array[state];
    }

    template <class Item>
    Line_Iter_Back<Item>&
    Line_Iter_Back<Item>::reset()
    {
        state = 0;

        return pax_self;
    }
} // pax
