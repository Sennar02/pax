#ifndef PAX_BASE_GRID_ITER_HPP
#define PAX_BASE_GRID_ITER_HPP

#include <pax/Base/define.hpp>

namespace pax
{
    template <class Item>
    struct Grid_Iter_Forw
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
        u64 lines = 0;

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
        u64
        col() const;

        /**
         * todo: Comment.
         */
        u64
        row() const;

        /**
         * todo: Comment.
         */
        Item&
        item() const;

        /**
         * todo: Comment.
         */
        Grid_Iter_Forw<Item>&
        reset();
    };

    template <class Item>
    struct Grid_Iter_Back
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
        u64 lines = 0;

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
        u64
        col() const;

        /**
         * todo: Comment.
         */
        u64
        row() const;

        /**
         * todo: Comment.
         */
        Item&
        item() const;

        /**
         * todo: Comment.
         */
        Grid_Iter_Back<Item>&
        reset();
    };
} // pax

#include <pax/Base/inline/Grid_Iter.inl>

#endif // PAX_BASE_GRID_ITER_HPP
