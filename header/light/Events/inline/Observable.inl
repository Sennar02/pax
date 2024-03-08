#include <light/Events/Observable.hpp>

namespace light
{
    template <class Type>
    bool
    Observable<Type>::insert(Observer<Type>& observ)
    {
        if ( observ.link == 0 ) {
            observ.link = this;
            observ.next   = list;

            if ( list != 0 )
                list->prev = &observ;

            list = &observ;

            return true;
        }

        return false;
    }

    template <class Type>
    bool
    Observable<Type>::remove(Observer<Type>& observ)
    {
        if ( observ.link == this ) {
            observ.link = 0;

            if ( list == &observ ) list = list->next;

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
    Observable<Type>::publish(const Type& event) const
    {
        Observer<Type>* node = list;

        for ( ; node != 0; node = node->next )
            node->receive(event);

        return true;
    }
} // light
