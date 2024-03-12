#ifndef PAX_MEMORY_BUMP_ALLOC_HPP
#define PAX_MEMORY_BUMP_ALLOC_HPP

#include <pax/Memory/define.hpp>
#include <pax/Memory/util.hpp>
#include <pax/Memory/Alloc.hpp>

namespace pax
{
    struct Bump_Alloc
        : public Alloc
    {
    public:
        /**
         *
         */
        u64 size = 0;

        /**
         *
         */
        s8* data = 0;

        /**
         *
         */
        s8* addr = 0;

    public:
        /**
         *
         */
        Bump_Alloc();

        /**
         *
         */
        Bump_Alloc(void* data, u64 size);

        /**
         *
         */
        void*
        reserve(u64 bytes, u8 align = 8u);

        /**
         *
         */
        bool
        reclaim(void* addr);

        /**
         *
         */
        Alloc&
        reset();
    };
} // pax

#endif // PAX_MEMORY_BUMP_ALLOC_HPP
