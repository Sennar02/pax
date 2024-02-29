#include <light/Memory/Array.hpp>

namespace light
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
    Array<Type>::Array(Alloc* alloc)
    {
        this->orig = alloc;
    }

    template <class Type>
    bool
    Array<Type>::create(u64 size, Alloc* alloc)
    {
        if ( data != 0 )
            return false;

        this->orig = alloc;

        return create(size);
    }

    template <class Type>
    bool
    Array<Type>::create(u64 size)
    {
        u64        bytes = LEN_TYPE * size;
        Opt<void*> block;

        if ( orig != 0 && data == 0 ) {
            block = orig->reserve(bytes, ALG_TYPE);

            if ( block.is_valid ) {
                this->data = (Type*) block.item;
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

        if ( orig != 0 && data != 0 ) {
            res = orig->reclaim(data);

            if ( res ) {
                this->data = 0;
                this->size = 0;
            }
        }

        return res;
    }

    template <class Type>
    Type&
    Array<Type>::operator[](u64 index)
    {
        #if LIGHT_TEST_BOUNDS
            if ( index >= size )
                light_panic("test-bounds", "index %lu exceeds %lu", index, size);
        #endif

        return data[index];
    }

    template <class Type>
    const Type&
    Array<Type>::operator[](u64 index) const
    {
        #if LIGHT_TEST_BOUNDS
            if ( index >= size )
                light_panic("test-bounds", "index %lu exceeds %lu", index, size);
        #endif

        return data[index];
    }
} // light

