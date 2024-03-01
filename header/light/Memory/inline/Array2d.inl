#include <light/Memory/Array2d.hpp>

namespace light
{
    template <class Type>
    Array2d<Type>::Array2d() {}

    template <class Type>
    Array2d<Type>::Array2d(void* data, v2u64 size)
    {
        u64 area = size[0] * size[1];

        if ( data != 0 && area != 0 ) {
            this->data = (Type*) data;
            this->size = area;
            this->cols = size[0];
            this->rows = size[1];
        }
    }

    template <class Type>
    Array2d<Type>::Array2d(v2u64 size, Alloc* alloc)
    {
        create(size, alloc);
    }

    template <class Type>
    bool
    Array2d<Type>::create(v2u64 size, Alloc* alloc)
    {
        u64        total = size[0] * size[1];
        u64        bytes = LEN_TYPE * total;
        Opt<void*> block;

        if ( alloc != 0 && data != 0 )
            return false;

        this->orig = alloc;

        if ( orig != 0 && data == 0 ) {
            block = orig->reserve(bytes, ALG_TYPE);

            if ( block.is_valid ) {
                this->data = (Type*) block.item;
                this->size = total;
                this->cols = size[0];
                this->rows = size[1];

                return true;
            }
        }

        return false;
    }

    template <class Type>
    bool
    Array2d<Type>::create(v2u64 size)
    {
        u64        total = size[0] * size[1];
        u64        bytes = LEN_TYPE * total;
        Opt<void*> block;

        if ( orig != 0 && data == 0 ) {
            block = orig->reserve(bytes, ALG_TYPE);

            if ( block.is_valid ) {
                this->data = (Type*) block.item;
                this->size = total;
                this->cols = size[0];
                this->rows = size[1];

                return true;
            }
        }

        return false;
    }

    template <class Type>
    bool
    Array2d<Type>::destroy()
    {
        bool res = false;

        if ( orig != 0 && data != 0 ) {
            res = orig->reclaim(data);

            if ( res ) {
                this->data = 0;
                this->size = 0;
                this->cols = 0;
                this->rows = 0;
            }
        }

        return res;
    }

    template <class Type>
    Type&
    Array2d<Type>::operator[](v2u64 index)
    {
        u64 i = index[0];
        u64 j = index[1];

        #if LIGHT_TEST_BOUNDS
            if ( i >= cols ) light_panic("test-bounds", "col %lu exceeds %lu", i, cols);
            if ( j >= rows ) light_panic("test-bounds", "row %lu exceeds %lu", j, rows);
        #endif

        return data[j * cols + i];
    }

    template <class Type>
    const Type&
    Array2d<Type>::operator[](v2u64 index) const
    {
        u64 i = index[0];
        u64 j = index[1];

        #if LIGHT_TEST_BOUNDS
            if ( i >= cols ) light_panic("test-bounds", "col %lu exceeds %lu", i, cols);
            if ( j >= rows ) light_panic("test-bounds", "row %lu exceeds %lu", j, rows);
        #endif

        return data[j * cols + i];
    }

    template <class Type>
    Type&
    Array2d<Type>::operator[](u64 index)
    {
        #if LIGHT_TEST_BOUNDS
            if ( index >= size )
                light_panic("test-bounds", "index %lu exceeds %lu", index, size);
        #endif

        return data[index];
    }

    template <class Type>
    const Type&
    Array2d<Type>::operator[](u64 index) const
    {
        #if LIGHT_TEST_BOUNDS
            if ( index >= size )
                light_panic("test-bounds", "index %lu exceeds %lu", index, size);
        #endif

        return data[index];
    }
} // light
