#include <pax/Signal/Observable.hpp>

namespace pax
{
    template <class Type>
    bool
    Observable<Type>::insert(Observer<Type>& observ)
    {
        if ( observ.link == 0 ) {
            observ.link = this;
            observ.next = list;

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
        auto* next = observ.next;
        auto* prev = observ.prev;

        if ( observ.link == this ) {
            if ( list == &observ )
                list = list->next;

            observ.link = 0;

            if ( next != 0 ) next->prev = prev;
            if ( prev != 0 ) prev->next = next;

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
} // pax
