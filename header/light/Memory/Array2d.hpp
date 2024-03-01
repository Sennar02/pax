#ifndef LIGHT_MEMORY_ARRAY_2D_HPP
#define LIGHT_MEMORY_ARRAY_2D_HPP

#include <light/Memory/define.hpp>
#include <light/Memory/Alloc.hpp>

namespace light
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
        Alloc* orig = 0;

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
        Array2d();

        /**
         *
         */
        Array2d(void* data, v2u64 size);

        /**
         *
         */
        Array2d(v2u64 size, Alloc* alloc);

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
        Type&
        operator[](u64 index);

        /**
         *
         */
        const Type&
        operator[](u64 index) const;
    };
} // light

#include <light/Memory/inline/Array2d.inl>

#endif // LIGHT_MEMORY_ARRAY_2D_HPP
