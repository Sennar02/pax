#ifndef LIGHT_BASE_OPT_HPP
#define LIGHT_BASE_OPT_HPP

#include <light/Base/define.hpp>

namespace light
{
    template <class Item>
    struct Opt
    {
    public:
        union {
            Item item;
        };

        bool full;

    public:
        Opt();

        Opt(Item item);
    };

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

#endif // LIGHT_BASE_OPT_HPP
