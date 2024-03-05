#ifndef LIGHT_SIGNAL_OBSERVER_HPP
#define LIGHT_SIGNAL_OBSERVER_HPP

#include <light/Signal/define.hpp>

namespace light
{
    template <class Type>
    struct Observer
    {
    public:
        /**
         *
         */
        Signal<Type>* sign = 0;

        /**
         *
         */
        Observer<Type>* next = 0;

        /**
         *
         */
        Observer<Type>* prev = 0;

    public:
        /**
         *
         */
        virtual void
        receive(const Type& value) = 0;
    };
} // light

#endif // LIGHT_ENGINE_OBSERVER_HPP
