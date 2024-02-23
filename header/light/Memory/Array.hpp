#ifndef LIGHT_MEMORY_ARRAY_HPP
#define LIGHT_MEMORY_ARRAY_HPP

namespace light
{
    template <class Type>
    struct Array
    {
    public:
        static const u64 LEN_TYPE =
            sizeof(Type);

    public:
        Type* data;
        u64   size;

    public:
        /**
         *
         */
        Array(u64 size = 0);

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
    Array<Type>::Array(u64 size)
        : data {0}
        , size {0}
    {
        if ( size != 0 ) {
            this->data = (Type*) calloc(1u, size * LEN_TYPE);

            if ( this->data != 0 )
                this->size = size;
        }
    }

    template <class Type>
    Type&
    Array<Type>::operator[](u64 index)
    {
        return data[index];
    }

    template <class Type>
    const Type&
    Array<Type>::operator[](u64 index) const
    {
        return data[index];
    }
} // light

#endif // LIGHT_MEMORY_ARRAY_HPP
