#ifndef LIGHT_MEMORY_ARRAY_HPP
#define LIGHT_MEMORY_ARRAY_HPP

#include <light/Memory/define.hpp>
#include <light/Memory/Alloc.hpp>

namespace light
{
    template <class Type>
    struct Array
    {
    public:
        static const u64 LEN_TYPE =
            sizeof(Type);

        static const u8 ALG_TYPE =
            alignof(Type);

    public:
        Alloc* alloc = 0;
        Type*  data = 0;
        u64    size = 0;

    public:
        /**
         *
         */
        Array();

        /**
         *
         */
        Array(void* data, u64 size);

        /**
         *
         */
        Array(Alloc* alloc);

        /**
         *
         */
        bool
        create(u64 size);

        /**
         *
         */
        bool
        destroy();

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
        this->alloc = alloc;
    }

    template <class Type>
    bool
    Array<Type>::create(u64 size)
    {
        u64        bytes = LEN_TYPE * size;
        Opt<void*> block;

        if ( alloc != 0 && data == 0 ) {
            block = alloc->reserve(bytes, ALG_TYPE);

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
