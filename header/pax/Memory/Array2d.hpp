#ifndef PAX_MEMORY_ARRAY_2D_HPP
#define PAX_MEMORY_ARRAY_2D_HPP

#include <pax/Memory/define.hpp>
#include <pax/Memory/Alloc.hpp>

namespace pax
{
    template <class Type>
    struct Array2d
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

        /**
         *
         */
        u64 cols = 0;

        /**
         *
         */
        u64 rows = 0;

    public:
        /**
         *
         */
        static Array2d<Type>
        build(void* data, v2u64 size);

        /**
         *
         */
        static Array2d<Type>
        build(v2u64 size, Alloc* alloc);

        /**
         *
         */
        bool
        create(v2u64 size, Alloc* alloc);

        /**
         *
         */
        bool
        create(v2u64 size);

        /**
         *
         */
        bool
        destroy();

        /**
         *
         */
        Type&
        operator[](v2u64 index);

        /**
         *
         */
        const Type&
        operator[](v2u64 index) const;

        /**
         *
         */
        Array<Type>
        operator[](u64 index);

        /**
         *
         */
        const Array<Type>
        operator[](u64 index) const;
    };
} // pax

#include <pax/Memory/inline/Array2d.inl>

#endif // PAX_MEMORY_ARRAY_2D_HPP
