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
        Array<void*> table = Array<void*>();

    public:
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
        remove(Observer<Type>& observ);

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
