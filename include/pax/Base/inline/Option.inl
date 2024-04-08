#include <pax/Base/Option.hpp>

namespace pax
{
    template <class Item>
    Option<Item>::Option()
    { }

    template <class Item>
    Option<Item>
    option_create(Item item)
    {
        Option<Item> option;

        option.item  = item;
        option.full = true;

        return option;
    }
} // pax
