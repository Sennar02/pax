#include <pax/Base/Option.hpp>

namespace pax
{
    template <class Item>
    Option<Item>
    option_create(Item item)
    {
        Option<Item> option;

        option.item  = item;
        option.valid = true;

        return option;
    }
} // pax