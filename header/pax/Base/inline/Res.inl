#include <pax/Base/Res.hpp>

namespace pax
{
    template <class Item, class Fail>
    Res<Item, Fail>::Res(Item item)
        : item {item}
        , is_valid {true}
    {}

    template <class Item, class Fail>
    Res<Item, Fail>::Res(Fail fail)
        : fail {fail}
    {}
} // pax
