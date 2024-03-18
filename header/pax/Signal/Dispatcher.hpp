#ifndef PAX_SIGNAL_DISPATCHER_HPP
#define PAX_SIGNAL_DISPATCHER_HPP

#include <pax/Signal/define.hpp>
#include <pax/Signal/Signal.hpp>
#include <pax/Signal/Observer.hpp>

namespace pax
{
    struct Dispatcher
    {
    public:
        /**
         *
         */
        Array<Array_List<void*>> table;

    public:
        /**
         *
         */
        static Dispatcher
        build(v2u64 size, Alloc* alloc);

        /**
         *
         */
        template <class Type>
        bool
        insert(Observer<Type>& observ);

        /**
         *
         */
        template <class Type>
        bool
        remove(u64 index);

        /**
         *
         */
        template <class Type>
        bool
        publish(const Type& event) const;
    };
} // pax

#include <pax/Signal/inline/Dispatcher.inl>

#endif // PAX_SIGNAL_DISPATCHER_HPP
