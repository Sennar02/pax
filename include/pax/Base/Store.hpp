#ifndef PAX_BASE_STORE_HPP
#define PAX_BASE_STORE_HPP

#include <pax/Base/define.hpp>

namespace pax
{
    template <typename Item, u64 Size>
    struct Store
    {
    public:
        /**
         * Amount of elements in the array.
         */
        static const u64 SIZE = Size;

    public:
        /**
         * Static array of elements.
         */
        Item data[Size];

    public:
        /**
         * Returns the element contained in a particular index.
         */
        Item&
        item(u64 index);

        /**
         * Returns the element contained in a particular index.
         */
        const Item&
        item(u64 index) const;

        /**
         * Returns the element contained in a particular index.
         */
        Item&
        operator()(u64 index);

        /**
         * Returns the element contained in a particular index.
         */
        const Item&
        operator()(u64 index) const;
    };
} // pax

#include <pax/Base/inline/Store.inl>

#endif // PAX_BASE_STORE_HPP