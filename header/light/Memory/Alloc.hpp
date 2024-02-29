#ifndef LIGHT_MEMORY_ALLOC_HPP
#define LIGHT_MEMORY_ALLOC_HPP

#include <light/Memory/define.hpp>

namespace light
{
    struct Alloc
    {
    public:
        /**
         *
         */
        virtual Opt<void*>
        reserve(u64 bytes, u8 align) = 0;

        /**
         *
         */
        virtual bool
        reclaim(void* addr) = 0;

        /**
         *
         */
        virtual void
        reset() = 0;
    };
} // light

#endif // LIGHT_MEMORY_ALLOC_HPP
