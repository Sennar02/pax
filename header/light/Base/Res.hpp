#ifndef LIGHT_BASE_RES_HPP
#define LIGHT_BASE_RES_HPP

#include <light/Base/define.hpp>

namespace light
{
    template <class Item, class Fail>
    struct Res
    {
    public:
        /**
         * Size in bytes of the item.
         */
        static const u64 LEN_ITEM = sizeof(Item);

        /**
         * Size in bytes of the failure information.
         */
        static const u64 LEN_FAIL = sizeof(Fail);

    public:
        union {
            /**
             * Actual item.
             */
            Item item;

            /**
             * Failure information.
             */
            Fail fail;
        };

        /**
         * Helper boolean used to determine if
         * the item exists or not. If the item
         * does not exist, it's certain that
         * additional failure information has
         * been provided.
         */
        bool full;

    public:
        /**
         * Constructor used to provide an item.
         */
        Res(Item item);

        /**
         * Constructor used to provide failure
         * information.
         */
        Res(Fail fail);
    };
} // light

#include <light/Base/inline/Res.inl>

#endif // LIGHT_BASE_RES_HPP
