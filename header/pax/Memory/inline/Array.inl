#include <pax/Memory/Array.hpp>

namespace pax
{
    template <class Type>
    Array<Type>::Array() {}

    template <class Type>
    Array<Type>::Array(void* data, u64 size)
    {
        if ( data != 0 && size != 0 ) {
            this->data = (Type*) data;
            this->size = size;
        }
    }

    template <class Type>
    Array<Type>::Array(u64 size, Alloc* alloc)
    {
        create(size, alloc);
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
        bool res = false;

        if ( alloc != 0 && data != 0 ) {
            res = alloc->reclaim(data);

            if ( res ) {
                this->data = 0;
                this->size = 0;
            }
        }

        return res;
    }

    template <class Type>
    Array<Type>&
    Array<Type>::fill(const Type& value)
    {
        for ( u64 i = 0; i < size; i += 1u )
            data[i] = value;

        return *this;
    }

    template <class Type>
    template <class Func, class... Args>
    Array<Type>&
    Array<Type>::fill(Func filler, Args... args)
    {
        for ( u64 i = 0; i < size; i += 1u )
            data[i] = filler(args...);

        return *this;
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
