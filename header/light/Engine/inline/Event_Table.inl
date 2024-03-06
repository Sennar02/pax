#include <light/Engine/Event_Table.hpp>

namespace light
{
    template <class Type>
    bool
    Event_Table::insert(Receiver<Type>& func)
    {
        if ( table[Type::TYPE] != 0 )
            return false;

        table[Type::TYPE] = (void*) &func;

        return true;
    }


    template <class Type>
    bool
    Event_Table::publish(Type& event)
    {
        u64   type = event.type();
        void* func = 0;

        if ( type == Type::TYPE ) {
            func = table[type];

            if ( func != 0 )
                event.sent |= ((Receiver<Type>*) func)->
                    receive(event);
        }

        return func != 0;
    }
} // light
