#include <pax/Signal/Dispatcher.hpp>

namespace pax
{
    template <class Type>
    bool
    Dispatcher::insert(Observer<Type>& item)
    {
        u64 kind = Type::KIND;

        if ( kind < table.size ) {
            Array_List<void*>* list = &table[kind];

            if ( list->insert((void*) &item, list->count) )
                return true;
        }

        return false;
    }

    template <class Type>
    bool
    Dispatcher::remove(u64 index)
    {
        u64 kind = Type::KIND;

        if ( kind < table.size ) {
            Array_List<void*>* list = &table[kind];

            if ( list->remove(index).is_valid )
                return true;
        }

        return false;
    }

    template <class Type>
    bool
    Dispatcher::publish(const Type& event) const
    {
        u64 kind = Type::KIND;

        if ( event.kind() == kind && kind < table.size ) {
            const Array_List<void*>* list = &table[kind];

            for ( u64 i = 0; i < list->count; i += 1u )
                ((Observer<Type>*) list->array.data[i])->receive(event);
        }

        return true;
    }
} // pax
