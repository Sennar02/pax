#include <pax/Memory/Array_List.hpp>

namespace pax
{
    template <class Type>
    Array_List<Type>
    Array_List<Type>::build(void* data, u64 size)
    {
        Array_List<Type> reslt;

        reslt.create(data, size);
        reslt.count = size;

        return reslt;
    }

    template <class Type>
    Array_List<Type>
    Array_List<Type>::build(u64 size, Alloc* alloc)
    {
        Array_List<Type> reslt;

        reslt.create(size, alloc);

        return reslt;
    }

    template <class Type>
    bool
    Array_List<Type>::create(u64 size, Alloc* alloc)
    {
        if ( count == 0 )
            return array.create(size, alloc);

        return false;
    }

    template <class Type>
    bool
    Array_List<Type>::create(u64 size)
    {
        if ( count == 0 )
            return array.create(size);

        return false;
    }

    template <class Type>
    bool
    Array_List<Type>::destroy()
    {
        if ( count == 0 )
            return array.destroy();

        return false;
    }

    template <class Type>
    bool
    Array_List<Type>::swap(u64 index, u64 other)
    {
        Type temp;

        if ( index == other ) return true;

        if ( index <= count && other <= count ) {
            temp = array.data[index];

            array.data[index] = array.data[other];
            array.data[other] = temp;

            return true;
        }

        return false;
    }

    template <class Type>
    bool
    Array_List<Type>::move(u64 index, s64 displ)
    {
        s64 direc = (displ > 0) - (displ < 0);
        u64 modif = (displ < 0) * (count - index);
        u64 limit = (displ > 0) * displ + count;
        u64 sourc = 0;
        u64 dstin = 0;

        if ( count + displ > array.size ) return false;

        for ( u64 i = 0; i < count - index; i += 1u ) {
            dstin = modif + direc * i;
            dstin = count - dstin;
            sourc = dstin - displ;

            if ( dstin <= limit && sourc <= limit )
                array.data[dstin] = array.data[sourc];
        }

        count += displ;

        return true;
    }

    template <class Type>
    bool
    Array_List<Type>::insert(Type item, u64 index)
    {
        bool reslt = index <= count;

        if ( reslt && move(index, 1) )
            array.data[index] = item;

        return reslt;
    }

    template <class Type>
    Opt<Type>
    Array_List<Type>::remove(u64 index)
    {
        Opt<Type> reslt = {};
        u64       other = count - 1u;

        if ( index < count ) {
            reslt = Opt<Type>::build(array.data[index]);

            if ( index != other )
                swap(index, other);

            move(other, -1);
        }

        return reslt;
    }
} // pax