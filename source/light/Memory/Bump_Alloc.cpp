#include <light/Memory/Bump_Alloc.hpp>

namespace light
{
    Bump_Alloc::Bump_Alloc() {}

    Bump_Alloc::Bump_Alloc(void* data, u64 size)
    {
        if ( data != 0 && size != 0 ) {
            this->data = (s8*) data;
            this->addr = (s8*) data;
            this->size = size;
        }
    }

    void*
    Bump_Alloc::reserve(u64 bytes, u8 align)
    {
        s8* pntr = addr + align_diff(addr, align, 0);
        s8* next = pntr + bytes;

        if ( bytes == 0 ) return 0;

        if ( is_power_of_two(align) == false )
            return 0;

        if ( next <= data + size ) {
            addr = next;

            for ( u64 i = 0; i < bytes; i += 1u )
                pntr[i] = 0;

            return pntr;
        }

        return 0;
    }

    bool
    Bump_Alloc::reclaim(void* addr)
    {
        return addr == 0;
    }

    Alloc&
    Bump_Alloc::reset()
    {
        addr = data;

        return *this;
    }
} // light
