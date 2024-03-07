#ifndef LIGHT_ENGINE_EVENT_SOURCE_HPP
#define LIGHT_ENGINE_EVENT_SOURCE_HPP

#include <light/Engine/define.hpp>
#include <light/Engine/Events/Observer.hpp>

namespace light
{
    template <class Type>
    struct Event_Source
    {
    public:
        /**
         *
         */
        Observer<Type>* list = 0;

    public:
        /**
         *
         */
        bool
        insert(Observer<Type>& observ);

        /**
         *
         */
        bool
        remove(Observer<Type>& observ);

        /**
         *
         */
        bool
        publish(const Type& event) const;
    };
} // light

#include <light/Engine/inline/Event_Source.inl>

#endif // LIGHT_ENGINE_EVENT_SOURCE_HPP
