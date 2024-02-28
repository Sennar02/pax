#ifndef LIGHT_MEMORY_ARRAY_2D_HPP
#define LIGHT_MEMORY_ARRAY_2D_HPP

#include <light/Memory/define.hpp>

namespace light
{
    template <class Type>
    struct Array2d
    {
    public:
        static const u64 LEN_TYPE =
            sizeof(Type);

    public:
        Type* data = 0;
        u64   size = 0;
        u64   cols = 0;
        u64   rows = 0;

    public:
        /**
         *
         */
        Array2d();

        /**
         *
         */
        Array2d(void* data, Vec2u size);

        /**
         *
         */
        Array2d(Vec2u size);

        /**
         *
         */
        Type&
        operator[](Vec2u index);

        /**
         *
         */
        const Type&
        operator[](Vec2u index) const;

        /**
         *
         */
        Type&
        operator[](u64 index);

        /**
         *
         */
        const Type&
        operator[](u64 index) const;
    };
} // light

namespace light
{
    template <class Type>
    Array2d<Type>::Array2d() {}

    template <class Type>
    Array2d<Type>::Array2d(void* data, Vec2u size)
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
    Array2d<Type>::Array2d(Vec2u size)
    {
        u64 area = size[0] * size[1];

        if ( area != 0 ) {
            this->data = (Type*) calloc(1u, area * LEN_TYPE);

            if ( this->data != 0 ) {
                this->size = area;
                this->cols = size[0];
                this->rows = size[1];
            }
        }
    }

    template <class Type>
    Type&
    Array2d<Type>::operator[](Vec2u index)
    {
        u64 i = index[0];
        u64 j = index[1];

        return data[j * cols + i];
    }

    template <class Type>
    const Type&
    Array2d<Type>::operator[](Vec2u index) const
    {
        u64 i = index[0];
        u64 j = index[1];

        return data[j * cols + i];
    }

    template <class Type>
    Type&
    Array2d<Type>::operator[](u64 index)
    {
        return data[index];
    }

    template <class Type>
    const Type&
    Array2d<Type>::operator[](u64 index) const
    {
        return data[index];
    }
} // light

#endif // LIGHT_MEMORY_ARRAY_2D_HPP
