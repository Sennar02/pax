#ifndef PAX_SIGNAL_DISPATCHER_HPP
#define PAX_SIGNAL_DISPATCHER_HPP

#include <pax/Signal/define.hpp>

namespace pax
{
    struct Dispatcher
    {
    public:
        /**
         * todo: Comment.
         */
        List<List<Invoked>> table;

    public:
        /**
         * Default constructor to make the compiler happy.
         */
        Dispatcher();

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
        insert(Invoker<void(Item)> func);

        /**
         * todo: Comment.
         */
        template <class Item>
        Option<Invoked>
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
