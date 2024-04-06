#ifndef PAX_BASE_ARRAY_2D_HPP
#define PAX_BASE_ARRAY_2D_HPP

#include <pax/Base/define.hpp>
#include <pax/Base/Vec2d.hpp>

namespace pax
{
    template <class Item>
    struct Array2d
    {
    public:
        /**
         * todo: Comment.
         */
        Item* data = 0;

        /**
         * todo: Comment.
         */
        v2u64 size = {};

        /**
         * todo: Comment.
         */
        u64 area = 0;

    public:
        /**
         *
         */
        bool
        acquire(Item* item, v2u64 size);

        /**
         * todo: Comment.
         */
        bool
        acquire(v2u64 size);

        /**
         * todo: Comment.
         */
        bool
        release();

        /**
         * todo: Comment.
         */
        Array<Item>
        as_array();

        /**
         * todo: Comment.
         */
        const Array<Item>
        as_array() const;

        /**
         * todo: Comment.
         */
        Array<Item>
        line(u64 row);

        /**
         * todo: Comment.
         */
        const Array<Item>
        line(u64 row) const;

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
        item(u64 col, u64 row);

        /**
         * todo: Comment.
         */
        const Item&
        item(u64 col, u64 row) const;

        /**
         * todo: Comment.
         */
        Item&
        item(v2u64 index);

        /**
         * todo: Comment.
         */
        const Item&
        item(v2u64 index) const;

        /**
         * todo: Comment.
         */
        Array<Item>
        operator[](u64 index);

        /**
         * todo: Comment.
         */
        const Array<Item>
        operator[](u64 index) const;

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

        /**
         * todo: Comment.
         */
        Item&
        operator()(u64 col, u64 row);

        /**
         * todo: Comment.
         */
        const Item&
        operator()(u64 col, u64 row) const;

        /**
         * todo: Comment.
         */
        Item&
        operator()(v2u64 index);

        /**
         * todo: Comment.
         */
        const Item&
        operator()(v2u64 index) const;
    };

    /**
     * todo: Comment.
     */
    template <class Item>
    Array2d<Item>
    array2d_create(Item* data, v2u64 size);

    /**
     * todo: Comment.
     */
    template <class Item>
    Array2d<Item>
    array2d_create(v2u64 size);
} // pax

#include <pax/Base/inline/Array2d.inl>

#endif // PAX_BASE_ARRAY_2D_HPP
