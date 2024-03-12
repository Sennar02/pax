#ifndef PAX_BASE_RES_HPP
#define PAX_BASE_RES_HPP

#include <pax/Base/define.hpp>

namespace pax
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
         * Size in bytes of the failure data.
         */
        static const u64 LEN_FAIL = sizeof(Fail);

    public:
        union {
            Item item;
            Fail fail;
        };

        /**
         * Determines if the item exists or not.
         */
        bool is_valid = false;

    public:
        /**
         * Constructor used to provide an item.
         */
        Res(Item item);

        /**
         * Constructor used to provide additional failure data.
         */
        Res(Fail fail);
    };
} // pax

#include <pax/Base/inline/Res.inl>

#endif // PAX_BASE_RES_HPP
