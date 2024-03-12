#ifndef PAX_SIGNAL_OBSERVABLE_HPP
#define PAX_SIGNAL_OBSERVABLE_HPP

#include <pax/Signal/define.hpp>
#include <pax/Signal/Observer.hpp>

namespace pax
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
} // pax

#include <pax/Signal/inline/Observable.inl>

#endif // PAX_SIGNAL_OBSERVABLE_HPP
