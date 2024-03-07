#ifndef LIGHT_ENGINE_EVENT_BROKER_HPP
#define LIGHT_ENGINE_EVENT_BROKER_HPP

#include <light/Engine/define.hpp>
#include <light/Engine/Events/Event.hpp>
#include <light/Engine/Events/Observer.hpp>

namespace light
{
    struct Event_Broker
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

#include <light/Engine/inline/Event_Broker.inl>

#endif // LIGHT_ENGINE_EVENT_BROKER_HPP
