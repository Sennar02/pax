#ifndef LIGHT_SIGNAL_SIGNAL_HPP
#define LIGHT_SIGNAL_SIGNAL_HPP

#include <light/Signal/define.hpp>
#include <light/Signal/Observer.hpp>

namespace light
{
    template <class Type>
    struct Signal
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
        publish(const Type& value);

        /**
         *
         */
        bool
        insert(Observer<Type>& item);

        /**
         *
         */
        bool
        remove(Observer<Type>& item);
    };
} // light

#include <light/Signal/inline/Signal.inl>

#endif // LIGHT_ENGINE_EVENT_QUEUE_HPP
