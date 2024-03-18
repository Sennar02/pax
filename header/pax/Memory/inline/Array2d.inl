#include <pax/Memory/Array2d.hpp>

namespace pax
{
    template <class Type>
    Array2d<Type>
    Array2d<Type>::build(void* data, v2u64 size)
    {
        Array2d<Type> reslt;
        u64           area = size[0] * size[1];

        if ( data != 0 && area != 0 ) {
            reslt.data = (Type*) data;
            reslt.size = area;
            reslt.cols = size[0];
            reslt.rows = size[1];
        }

        return reslt;
    }

    template <class Type>
    Array2d<Type>
    Array2d<Type>::build(v2u64 size, Alloc* alloc)
    {
        Array2d<Type> reslt;

        reslt.create(size, alloc);

        return reslt;
    }

    template <class Type>
    bool
    Array2d<Type>::create(v2u64 size, Alloc* alloc)
    {
        u64   total = size[0] * size[1];
        u64   bytes = LEN_TYPE * total;
        void* block = 0;

        if ( data != 0 ) return false;

        this->alloc = alloc;

        if ( alloc != 0 && data == 0 ) {
            block = alloc->reserve(bytes, ALG_TYPE);

            if ( block != 0 ) {
                this->data = (Type*) block;
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
        u64   total = size[0] * size[1];
        u64   bytes = LEN_TYPE * total;
        void* block = 0;

        if ( alloc != 0 && data == 0 ) {
            block = alloc->reserve(bytes, ALG_TYPE);

            if ( block != 0 ) {
                this->data = (Type*) block;
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
        bool reslt = false;

        if ( alloc != 0 && data != 0 ) {
            reslt = alloc->reclaim(data);

            if ( reslt ) {
                this->data = 0;
                this->size = 0;
                this->cols = 0;
                this->rows = 0;
            }
        }

        return reslt;
    }

    template <class Type>
    Type&
    Array2d<Type>::operator[](v2u64 index)
    {
        u64 r = index[0];
        u64 c = index[1];

        #if PAX_TEST_BOUNDS
            if ( c >= cols ) pax_panic("test-bounds", "col %lu exceeds %lu", c, cols);
            if ( r >= rows ) pax_panic("test-bounds", "row %lu exceeds %lu", r, rows);
        #endif

        return data[r * cols + c];
    }

    template <class Type>
    const Type&
    Array2d<Type>::operator[](v2u64 index) const
    {
        u64 r = index[0];
        u64 c = index[1];

        #if PAX_TEST_BOUNDS
            if ( c >= cols ) pax_panic("test-bounds", "col %lu exceeds %lu", c, cols);
            if ( r >= rows ) pax_panic("test-bounds", "row %lu exceeds %lu", r, rows);
        #endif

        return data[r * cols + c];
    }

    template <class Type>
    Array<Type>
    Array2d<Type>::operator[](u64 index)
    {
        #if PAX_TEST_BOUNDS
            if ( index >= rows )
                pax_panic("test-bounds", "row %lu exceeds %lu", index, rows);
        #endif

        return Array<Type>(data + cols * index, cols);
    }

    template <class Type>
    const Array<Type>
    Array2d<Type>::operator[](u64 index) const
    {
        #if PAX_TEST_BOUNDS
            if ( index >= rows )
                pax_panic("test-bounds", "row %lu exceeds %lu", index, rows);
        #endif

        return Array<Type>(data + cols * index, cols);
    }
} // pax
