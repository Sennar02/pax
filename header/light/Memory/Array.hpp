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
        /**
         *
         */
        static const u64 LEN_TYPE =
            sizeof(Type);

        /**
         *
         */
        static const u8 ALG_TYPE =
            alignof(Type);

    public:
        /**
         *
         */
        Alloc* alloc = 0;

        /**
         *
         */
        Type* data = 0;

        /**
         *
         */
        u64 size = 0;

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
        create(u64 size, Alloc* alloc);

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

#include <light/Memory/inline/Array.inl>

#endif // LIGHT_MEMORY_ARRAY_HPP
