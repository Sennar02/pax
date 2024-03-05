#ifndef LIGHT_BASE_OPT_HPP
#define LIGHT_BASE_OPT_HPP

#include <light/Base/define.hpp>

namespace light
{
    template <class Item>
    struct Opt
    {
    public:
        /**
         * Size in bytes of the item.
         */
        static const u64 LEN_ITEM = sizeof(Item);

    public:
        union {
            Item item;
        };

        /**
         * Determines if the item exists or not.
         */
        bool is_valid = false;

    public:
        /**
         * Default constructor to make the compiler happy.
         */
        Opt();

        /**
         * Constructor used to provide an item.
         */
        Opt(Item item);
    };
} // light

#include <light/Base/inline/Opt.inl>

#endif // LIGHT_BASE_OPT_HPP
