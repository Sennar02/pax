#include <light/Base/Opt.hpp>

namespace light
{
    template <class Item>
    Opt<Item>::Opt() {}

    template <class Item>
    Opt<Item>::Opt(Item item)
        : item {item}
        , is_valid {true}
    {}
} // light
