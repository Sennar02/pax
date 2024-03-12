#include <pax/Signal/Dispatcher.hpp>

namespace pax
{
    template <class Type>
    bool
    Dispatcher::insert(Observer<Type>& observ)
    {
        auto* list = (Observer<Type>*) table[Type::KIND];

        if ( observ.link == 0 ) {
            observ.link = this;
            observ.next = list;

            if ( list != 0 )
                list->prev = &observ;

            table[Type::KIND] = &observ;

            return true;
        }

        return false;
    }

    template <class Type>
    bool
    Dispatcher::remove(Observer<Type>& observ)
    {
        auto* next = observ.next;
        auto* prev = observ.prev;
        auto* list = (Observer<Type>*) table[Type::KIND];

        if ( observ.link == this ) {
            if ( list == &observ )
                table[Type::KIND] = list->next;

            observ.link = 0;

            if ( next != 0 ) next->prev = prev;
            if ( prev != 0 ) prev->next = next;

            return true;
        }

        return false;
    }

    template <class Type>
    bool
    Dispatcher::publish(const Type& event) const
    {
        auto* node = (Observer<Type>*) table[Type::KIND];

        if ( event.kind() == Type::KIND ) {
            for ( ; node != 0; node = node->next )
                node->receive(event);

            return true;
        }

        return false;
    }
} // pax
