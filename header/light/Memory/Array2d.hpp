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
        Type* data;
        u64   size;
        u64   width;

    public:
        /**
         *
         */
        Array2d();

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
    Array2d<Type>::Array2d()
        : data {0}
        , size {0}
        , width {0}
    {}

    template <class Type>
    Array2d<Type>::Array2d(Vec2u size)
        : Array2d()
    {
        u64 area = size[0] * size[1];

        if ( area != 0 ) {
            this->data = (Type*) calloc(1u, area * LEN_TYPE);

            if ( this->data != 0 ) {
                this->size  = area;
                this->width = size[0];
            }
        }
    }

    template <class Type>
    Type&
    Array2d<Type>::operator[](Vec2u index)
    {
        u64 i = index[0];
        u64 j = index[1];

        return data[j * width + i];
    }

    template <class Type>
    const Type&
    Array2d<Type>::operator[](Vec2u index) const
    {
        u64 i = index[0];
        u64 j = index[1];

        return data[j * width + i];
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
