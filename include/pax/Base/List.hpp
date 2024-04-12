#ifndef PAX_BASE_LIST_HPP
#define PAX_BASE_LIST_HPP

#include <pax/Base/define.hpp>
#include <pax/Base/math.hpp>
#include <pax/Base/Vec2d.hpp>

namespace pax
{
    template <class Item>
    struct List
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

        /**
         * todo: Comment.
         */
        u64 count = 0;

    public:
        /**
         * Default constructor to make the compiler happy.
         */
        List();

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
        is_empty() const;

        /**
         * todo: Comment.
         */
        bool
        is_full() const;

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
         * todo: Test.
         */
        bool
        push(u64 index, s64 displ);

        /**
         * todo: Comment.
         */
        template <class Func>
        List<Item>&
        loop(v2u64 range, Func func);

        /**
         * todo: Comment.
         */
        template <class Func>
        const List<Item>&
        loop(v2u64 range, Func func) const;

        /**
         * todo: Comment.
         */
        Option<u64>
        insert(Item item, u64 index);

        /**
         * todo: Comment.
         */
        Option<Item>
        remove(u64 index);

        /**
         * todo: Comment.
         */
        Option<u64>
        insert_push(Item item, u64 index);

        /**
         * todo: Comment.
         */
        Option<Item>
        remove_push(u64 index);

        /**
         * todo: Comment.
         */
        List<Item>&
        clear();

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
    List<Item>
    list_create(Item* data, u64 size);

    /**
     * todo: Comment.
     */
    template <class Item>
    List<Item>
    list_create(u64 size);

    /**
     * todo: Comment.
     */
    template <class Item>
    List<Item>&
    list_shuffle(List<Item>& list, v2u64 range = {0, MAX_U64});
} // pax

#include <pax/Base/inline/List.inl>

#endif // PAX_BASE_LIST_HPP
