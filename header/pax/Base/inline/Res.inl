#include <pax/Base/Res.hpp>

namespace pax
{
    template <class Item, class Fail>
    Res<Item, Fail>
    Res<Item, Fail>::build(Item item)
    {
        Res<Item, Fail> reslt;

        reslt.item     = item;
        reslt.is_valid = true;

        return reslt;
    }

    template <class Item, class Fail>
    Res<Item, Fail>
    Res<Item, Fail>::build(Fail fail)
    {
        Res<Item, Fail> reslt;

        reslt.fail     = fail;
        reslt.is_valid = false;

        return reslt;
    }
} // pax
