#ifndef PAX_SIGNAL_OBSERVER_HPP
#define PAX_SIGNAL_OBSERVER_HPP

#include <pax/Signal/define.hpp>

namespace pax
{
    template <class Type>
    struct Observer
    {
    public:
        /**
         *
         */
        void* link = 0;

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
        receive(const Type& event) = 0;
    };
} // pax

#endif // PAX_SIGNAL_OBSERVER_HPP
