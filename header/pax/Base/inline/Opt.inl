#include <pax/Base/Opt.hpp>

namespace pax
{
    template <class Item>
    Opt<Item>::Opt() {}

    template <class Item>
    Opt<Item>::Opt(Item item)
        : item {item}
        , is_valid {true}
    {}
} // pax
