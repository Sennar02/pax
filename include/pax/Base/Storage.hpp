#ifndef PAX_BASE_STORAGE_HPP
#define PAX_BASE_STORAGE_HPP

#include <pax/Base/define.hpp>
#include <pax/Base/math.hpp>
#include <pax/Base/Vec2d.hpp>

namespace pax
{
    template <typename Item, u64 Size>
    struct Storage
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
    Storage<Item, Size>&
    shuffle(Storage<Item, Size>& storage);

    /**
     * todo: Comment.
     */
    template <class Item, u64 Size>
    bool
    swap(Storage<Item, Size>& storage, u64 index, u64 other);

    /**
     * todo: Comment.
     */
    template <class Item, u64 Size>
    Line_Iter_Forw<const Item>
    iter_forw_create(const Storage<Item, Size>& storage);

    /**
     * todo: Comment.
     */
    template <class Item, u64 Size>
    Line_Iter_Forw<Item>
    iter_forw_create(Storage<Item, Size>& storage);

    /**
     * todo: Comment.
     */
    template <class Item, u64 Size>
    Line_Iter_Back<const Item>
    iter_back_create(const Storage<Item, Size>& storage);

    /**
     * todo: Comment.
     */
    template <class Item, u64 Size>
    Line_Iter_Back<Item>
    iter_back_create(Storage<Item, Size>& storage);
} // pax

#include <pax/Base/inline/Storage.inl>

#endif // PAX_BASE_STORAGE_HPP
