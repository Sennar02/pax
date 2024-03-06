#ifndef LIGHT_ENGINE_EVENT_TABLE_HPP
#define LIGHT_ENGINE_EVENT_TABLE_HPP

#include <light/Engine/define.hpp>
#include <light/Engine/Event.hpp>
#include <light/Engine/Receiver.hpp>

namespace light
{
    struct Event_Table
    {
    public:
        Array<void*> table = Array<void*>();

    public:
        /**
         *
         */
        template <class Type>
        bool
        insert(Receiver<Type>& func);

        /**
         *
         */
        template <class Type>
        bool
        publish(Type& event);
    };
} // light

#include <light/Engine/inline/Event_Table.inl>

#endif // LIGHT_ENGINE_EVENT_TABLE_HPP
