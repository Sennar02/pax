#ifndef PAX_BASE_LINE_ITER_HPP
#define PAX_BASE_LINE_ITER_HPP

#include <pax/Base/define.hpp>

namespace pax
{
    template <class Item>
    struct Line_Iter_Forw
    {
    public:
        /**
         * todo: Comment.
         */
        Item* array = 0;

        /**
         * todo: Comment.
         */
        u64 limit = 0;

        /**
         * todo: Comment.
         */
        u64 state = 0;

    public:
        /**
         * todo: Comment.
         */
        bool
        has_next() const;

        /**
         * todo: Comment.
         */
        Item&
        next();

        /**
         * todo: Comment.
         */
        u64
        index() const;

        /**
         * todo: Comment.
         */
        Item&
        item() const;

        /**
         * todo: Comment.
         */
        Line_Iter_Forw<Item>&
        reset();
    };

    template <class Item>
    struct Line_Iter_Back
    {
    public:
        /**
         * todo: Comment.
         */
        Item* array = 0;

        /**
         * todo: Comment.
         */
        u64 limit = 0;

        /**
         * todo: Comment.
         */
        u64 state = 0;

    public:
        /**
         * todo: Comment.
         */
        bool
        has_next() const;

        /**
         * todo: Comment.
         */
        Item&
        next();

        /**
         * todo: Comment.
         */
        u64
        index() const;

        /**
         * todo: Comment.
         */
        Item&
        item() const;

        /**
         * todo: Comment.
         */
        Line_Iter_Back<Item>&
        reset();
    };
} // pax

#include <pax/Base/inline/Line_Iter.inl>

#endif // PAX_BASE_LINE_ITER_HPP
