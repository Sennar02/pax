#ifndef PAX_MEMORY_ALLOC_HPP
#define PAX_MEMORY_ALLOC_HPP

#include <pax/Memory/define.hpp>

namespace pax
{
    struct Alloc
    {
    public:
        /**
         *
         */
        virtual void*
        reserve(u64 bytes, u8 align) = 0;

        /**
         *
         */
        virtual bool
        reclaim(void* addr) = 0;

        /**
         *
         */
        virtual Alloc&
        reset() = 0;
    };
} // pax

#endif // PAX_MEMORY_ALLOC_HPP
