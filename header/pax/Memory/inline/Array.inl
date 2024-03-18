#include <pax/Memory/Array.hpp>

namespace pax
{
    template <class Type>
    Array<Type>
    Array<Type>::build(void* data, u64 size)
    {
        Array<Type> reslt;

        if ( data != 0 && size != 0 ) {
            reslt.data = (Type*) data;
            reslt.size = size;
        }

        return reslt;
    }

    template <class Type>
    Array<Type>
    Array<Type>::build(u64 size, Alloc* alloc)
    {
        Array<Type> reslt;

        reslt.create(size, alloc);

        return reslt;
    }

    template <class Type>
    bool
    Array<Type>::create(u64 size, Alloc* alloc)
    {
        u64   bytes = LEN_TYPE * size;
        void* block = 0;

        if ( data != 0 ) return false;

        this->alloc = alloc;

        if ( alloc != 0 && data == 0 ) {
            block = alloc->reserve(bytes, ALG_TYPE);

            if ( block != 0 ) {
                this->data = (Type*) block;
                this->size = size;

                return true;
            }
        }

        return false;

    }

    template <class Type>
    bool
    Array<Type>::create(u64 size)
    {
        u64   bytes = LEN_TYPE * size;
        void* block = 0;

        if ( alloc != 0 && data == 0 ) {
            block = alloc->reserve(bytes, ALG_TYPE);

            if ( block != 0 ) {
                this->data = (Type*) block;
                this->size = size;

                return true;
            }
        }

        return false;
    }

    template <class Type>
    bool
    Array<Type>::destroy()
    {
        bool reslt = false;

        if ( alloc != 0 && data != 0 ) {
            reslt = alloc->reclaim(data);

            if ( reslt ) {
                this->data = 0;
                this->size = 0;
            }
        }

        return reslt;
    }

    template <class Type>
    Type&
    Array<Type>::operator[](u64 index)
    {
        #if PAX_TEST_BOUNDS
            if ( index >= size )
                pax_panic("test-bounds", "index %lu exceeds %lu", index, size);
        #endif

        return data[index];
    }

    template <class Type>
    const Type&
    Array<Type>::operator[](u64 index) const
    {
        #if PAX_TEST_BOUNDS
            if ( index >= size )
                pax_panic("test-bounds", "index %lu exceeds %lu", index, size);
        #endif

        return data[index];
    }
} // pax
