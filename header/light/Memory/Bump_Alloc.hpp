#ifndef LIGHT_MEMORY_BUMP_ALLOC_HPP
#define LIGHT_MEMORY_BUMP_ALLOC_HPP

#include <light/Memory/define.hpp>
#include <light/Memory/util.hpp>
#include <light/Memory/Alloc.hpp>

namespace light
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
        void
        reset();
    };
} // light

#endif // LIGHT_MEMORY_BUMP_ALLOC_HPP
