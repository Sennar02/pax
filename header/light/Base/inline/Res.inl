#include <light/Base/Res.hpp>

namespace light
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
} // light
