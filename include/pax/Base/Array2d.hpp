#ifndef PAX_BASE_ARRAY_2D_HPP
#define PAX_BASE_ARRAY_2D_HPP

#include <pax/Base/define.hpp>
#include <pax/Base/Grid_Iter.hpp>
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
         * Default constructor to make the compiler happy.
         */
        Array2d();

        /**
         * todo: Comment.
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
        bool
        contains(u64 index) const;

        /**
         * todo: Comment.
         */
        bool
        contains(u64 col, u64 row) const;

        /**
         * todo: Comment.
         */
        bool
        contains(v2u64 index) const;

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
        line(u64 index);

        /**
         * todo: Comment.
         */
        const Array<Item>
        line(u64 index) const;

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
    array2d_create(Item* data, u64 cols, u64 rows);

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
    array2d_create(u64 cols, u64 rows);

    /**
     * todo: Comment.
     */
    template <class Item>
    Array2d<Item>
    array2d_create(v2u64 size);

    /**
     * todo: Comment.
     */
    template <class Item>
    Array2d<Item>&
    shuffle(Array2d<Item>& array);

    /**
     * todo: Comment.
     */
    template <class Item>
    bool
    swap(Array2d<Item>& array, u64 index, u64 other);

    /**
     * todo: Comment.
     */
    template <class Item>
    bool
    swap(Array2d<Item>& array, u64 col_1, u64 row_1, u64 col_2, u64 row_2);

    /**
     * todo: Comment.
     */
    template <class Item>
    bool
    swap(Array2d<Item>& array, v2u64 index, v2u64 other);

    /**
     * todo: Comment.
     */
    template <class Item>
    Grid_Iter_Forw<const Item>
    iter_forw_create(const Array2d<Item>& array);

    /**
     * todo: Comment.
     */
    template <class Item>
    Grid_Iter_Forw<Item>
    iter_forw_create(Array2d<Item>& array);

    /**
     * todo: Comment.
     */
    template <class Item>
    Grid_Iter_Back<const Item>
    iter_back_create(const Array2d<Item>& array);

    /**
     * todo: Comment.
     */
    template <class Item>
    Grid_Iter_Back<Item>
    iter_back_create(Array2d<Item>& array);
} // pax

#include <pax/Base/inline/Array2d.inl>

#endif // PAX_BASE_ARRAY_2D_HPP
