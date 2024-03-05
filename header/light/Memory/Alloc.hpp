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

    /**
     *
     */
    template <class Type, class... Args>
    Type*
    reserve(Alloc& alloc, Args... args);
} // light

#include <light/Memory/inline/Alloc.inl>

#endif // LIGHT_MEMORY_ALLOC_HPP
