#ifndef LIGHT_EVENTS_OBSERVABLE_HPP
#define LIGHT_EVENTS_OBSERVABLE_HPP

#include <light/Events/define.hpp>
#include <light/Events/Observer.hpp>

namespace light
{
    template <class Type>
    struct Observable
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

#include <light/Events/inline/Observable.inl>

#endif // LIGHT_EVENTS_OBSERVABLE_HPP
