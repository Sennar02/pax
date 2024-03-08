#ifndef LIGHT_EVENTS_DISPATCHER_HPP
#define LIGHT_EVENTS_DISPATCHER_HPP

#include <light/Events/define.hpp>
#include <light/Events/Event.hpp>
#include <light/Events/Observer.hpp>

namespace light
{
    struct Dispatcher
    {
    public:
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
} // light

#include <light/Events/inline/Dispatcher.inl>

#endif // LIGHT_EVENTS_DISPATCHER_HPP
