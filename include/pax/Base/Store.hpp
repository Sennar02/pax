#ifndef PAX_BASE_STORE_HPP
#define PAX_BASE_STORE_HPP

#include <pax/Base/define.hpp>
#include <pax/Base/math.hpp>
#include <pax/Base/Vec2d.hpp>

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
         * todo: Comment.
         */
        bool
        contains(u64 index) const;

        /**
         * todo: Comment.
         */
        bool
        contains(v2u64 index) const;

        /**
         * todo: Comment.
         */
        u64
        clamp(u64 index) const;

        /**
         * todo: Comment.
         */
        v2u64
        clamp(v2u64 index) const;

        /**
         * todo: Comment.
         */
        bool
        swap(u64 index, u64 other);

        /**
         * todo: Comment.
         */
        template <class Func>
        Store<Item, Size>&
        loop(v2u64 range, Func func);

        /**
         * todo: Comment.
         */
        template <class Func>
        const Store<Item, Size>&
        loop(v2u64 range, Func func) const;

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

    /**
     * todo: Comment.
     */
    template <class Item, u64 Size>
    Store<Item, Size>&
    store_shuffle(Store<Item, Size>& store, v2u64 range = {0, MAX_U64});
} // pax

#include <pax/Base/inline/Store.inl>

#endif // PAX_BASE_STORE_HPP
