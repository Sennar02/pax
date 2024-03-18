#include <pax/Base/Opt.hpp>

namespace pax
{
    template <class Item>
    Opt<Item>
    Opt<Item>::build(Item item)
    {
        Opt<Item> reslt;

        reslt.item     = item;
        reslt.is_valid = true;

        return reslt;
    }
} // pax
