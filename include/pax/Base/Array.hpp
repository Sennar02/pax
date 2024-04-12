#ifndef PAX_BASE_ARRAY_HPP
#define PAX_BASE_ARRAY_HPP

#include <pax/Base/define.hpp>
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
        Array<Item>&
        loop(v2u64 range, Func func);

        /**
         * todo: Comment.
         */
        template <class Func>
        const Array<Item>&
        loop(v2u64 range, Func func) const;

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
    array_shuffle(Array<Item>& array, v2u64 range = {0, MAX_U64});
} // pax

#include <pax/Base/inline/Array.inl>

#endif // PAX_BASE_ARRAY_HPP
