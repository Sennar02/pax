#include <light/Signal/Signal.hpp>

namespace light
{
    template <class Type>
    bool
    Signal<Type>::publish(const Type& value)
    {
        Observer<Type>* node = list;

        for ( ; node != 0; node = node->next )
            node->receive(value);

        return true;
    }

    template <class Type>
    bool
    Signal<Type>::insert(Observer<Type>& item)
    {
        if ( item.sign == 0 ) {
            item.sign = this;
            item.next = list;

            if ( list != 0 )
                list->prev = &item;

            list = &item;

            return true;
        }

        return false;
    }

    template <class Type>
    bool
    Signal<Type>::remove(Observer<Type>& item)
    {
        if ( item.sign == this ) {
            item.sign = 0;

            if ( list == &item ) list = list->next;

            if ( item.next != 0 )
                item.next->prev = item.prev;

            if ( item.prev != 0 )
                item.prev->next = item.next;

            return true;
        }

        return false;
    }
} // light
