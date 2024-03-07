#ifndef LIGHT_ENGINE_OBSERVER_HPP
#define LIGHT_ENGINE_OBSERVER_HPP

#include <light/Engine/define.hpp>

namespace light
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
} // light

#endif // LIGHT_ENGINE_OBSERVER_HPP
