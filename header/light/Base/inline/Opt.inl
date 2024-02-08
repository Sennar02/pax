#include <light/Base/Opt.hpp>

namespace light
{
    template <class Item>
    Opt<Item>::Opt()
        : full {false}
    {}

    template <class Item>
    Opt<Item>::Opt(Item item)
        : item {item}
        , full {true}
    {}
} // light
