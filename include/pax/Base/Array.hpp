#ifndef PAX_BASE_ARRAY_HPP
#define PAX_BASE_ARRAY_HPP

#include <pax/Base/define.hpp>
#include <pax/Base/Line_Iter.hpp>
#include <pax/Base/math.hpp>
#include <pax/Base/Vec2d.hpp>

namespace pax
{
    template <class Item>
    struct Array
    {
    public:
        /**
         * todo: Comment.
         */
        Item* data = 0;

        /**
         * todo: Comment.
         */
        u64 size = 0;

    public:
        /**
         * Default constructor to make the compiler happy.
         */
        Array();

        /**
         * todo: Comment.
         */
        bool
        acquire(Item* data, u64 size);

        /**
         * todo: Comment.
         */
        bool
        acquire(u64 size);

        /**
         * todo: Comment.
         */
        bool
        release();

        /**
         * todo: Comment.
         */
        bool
        contains(u64 index) const;

        /**
         * todo: Comment.
         */
        Item&
        item(u64 index);

        /**
         * todo: Comment.
         */
        const Item&
        item(u64 index) const;

        /**
         * todo: Comment.
         */
        Item&
        operator()(u64 index);

        /**
         * todo: Comment.
         */
        const Item&
        operator()(u64 index) const;
    };

    /**
     * todo: Comment.
     */
    template <class Item>
    Array<Item>
    array_create(Item* data, u64 size);

    /**
     * todo: Comment.
     */
    template <class Item>
    Array<Item>
    array_create(u64 size);

    /**
     * todo: Comment.
     */
    template <class Item>
    Array<Item>&
    shuffle(Array<Item>& array);

    /**
     * todo: Comment.
     */
    template <class Item>
    bool
    swap(Array<Item>& array, u64 index, u64 other);

    /**
     * todo: Comment.
     */
    template <class Item>
    Line_Iter_Forw<const Item>
    iter_forw_create(const Array<Item>& array);

    /**
     * todo: Comment.
     */
    template <class Item>
    Line_Iter_Forw<Item>
    iter_forw_create(Array<Item>& array);

    /**
     * todo: Comment.
     */
    template <class Item>
    Line_Iter_Back<const Item>
    iter_back_create(const Array<Item>& array);

    /**
     * todo: Comment.
     */
    template <class Item>
    Line_Iter_Back<Item>
    iter_back_create(Array<Item>& array);
} // pax

#include <pax/Base/inline/Array.inl>

#endif // PAX_BASE_ARRAY_HPP
