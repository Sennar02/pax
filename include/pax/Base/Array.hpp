#ifndef PAX_BASE_ARRAY_HPP
#define PAX_BASE_ARRAY_HPP

#include <pax/Base/define.hpp>

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
} // pax

#include <pax/Base/inline/Array.inl>

#endif // PAX_BASE_ARRAY_HPP
