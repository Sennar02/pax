#ifndef PAX_MEMORY_POOL_ALLOC_HPP
#define PAX_MEMORY_POOL_ALLOC_HPP

#include <pax/Memory/define.hpp>
#include <pax/Memory/util.hpp>
#include <pax/Memory/Alloc.hpp>

namespace pax
{
    struct Pool_Alloc
        : public Alloc
    {
    public:
        struct Node;
        struct Pref;

        /**
         *
         */
        u64 size = 0;

        /**
         *
         */
        u64 page = 0;

        /**
         *
         */
        s8* data = 0;

        /**
         *
         */
        Node* list = 0;

    public:
        /**
         *
         */
        Pool_Alloc();

        /**
         *
         */
        Pool_Alloc(void* data, u64 size, u64 page, u8 align = 8u);

        /**
         *
         */
        void*
        reserve(u64 bytes, u8 align = 1u);

        /**
         *
         */
        void*
        reserve();

        /**
         *
         */
        bool
        reclaim(void* addr);

        /**
         *
         */
        Alloc&
        reset(u64 page, u8 align = 8u);

        /**
         *
         */
        Alloc&
        reset();

    private:
        /**
         *
         */
        bool
        insert(void* addr);

        /**
         *
         */
        s8*
        remove(u64 bytes, u8 align);
    };
} // pax

#endif // PAX_MEMORY_POOL_ALLOC_HPP
