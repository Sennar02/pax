#ifndef LIGHT_ENGINE_RECEIVER_HPP
#define LIGHT_ENGINE_RECEIVER_HPP

#include <light/Engine/define.hpp>

namespace light
{
    template <class Type>
    struct Receiver
    {
    public:
        /**
         *
         */
        virtual bool
        receive(const Type& event) = 0;
    };
} // light

#define receiver(Name, Type, body) \
    struct Name : public Receiver<Type> { body };

#endif // LIGHT_ENGINE_RECEIVER_HPP
