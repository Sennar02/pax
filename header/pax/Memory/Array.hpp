#ifndef PAX_MEMORY_ARRAY_HPP
#define PAX_MEMORY_ARRAY_HPP

#include <pax/Memory/define.hpp>
#include <pax/Memory/Alloc.hpp>

namespace pax
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
        static Array<Type>
        build(void* data, u64 size);

        /**
         *
         */
        static Array<Type>
        build(u64 size, Alloc* alloc);

        /**
         *
         */
        bool
        create(u64 size, Alloc* alloc);

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
} // pax

#include <pax/Memory/inline/Array.inl>

#endif // PAX_MEMORY_ARRAY_HPP
