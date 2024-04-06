#ifndef PAX_SIGNAL_DISPATCHER_HPP
#define PAX_SIGNAL_DISPATCHER_HPP

#include <pax/Signal/define.hpp>

namespace pax
{
    struct Dispatcher
    {
    public:
        struct Holder;

    public:
        /**
         * todo: Comment.
         */
        List<List<Holder>> table;

    public:
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
        template <class Item>
        Option<u64>
        insert(void (*func) (Item));

        /**
         * todo: Comment.
         */
        template <class Item, class Ctxt>
        Option<u64>
        insert(void (*func) (Item, Ctxt*), Ctxt& ctxt);

        /**
         * todo: Comment.
         */
        template <class Item>
        Option<void*>
        remove(u64 index);

        /**
         * todo: Comment.
         */
        template <class Item>
        bool
        publish(Item item) const;
    };
} // pax

#include <pax/Signal/inline/Dispatcher.inl>

#endif // PAX_SIGNAL_DISPATCHER_HPP