#include <light/Events/Dispatcher.hpp>

namespace light
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
        auto* list = (Observer<Type>*) table[Type::KIND];

        if ( observ.link == this ) {
            observ.link = 0;

            if ( list == &observ ) table[Type::KIND] = list->next;

            if ( observ.next != 0 )
                observ.next->prev = observ.prev;

            if ( observ.prev != 0 )
                observ.prev->next = observ.next;

            return true;
        }

        return false;
    }

    template <class Type>
    bool
    Dispatcher::publish(const Type& event) const
    {
        Observer<Type>* node = 0;

        if ( event.kind() == Type::KIND ) {
            node = (Observer<Type>*) table[Type::KIND];

            for ( ; node != 0; node = node->next )
                node->receive(event);

            return true;
        }

        return false;
    }
} // light
