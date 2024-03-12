#include <pax/Memory/Builder.hpp>
#include <new>

namespace pax
{
    template <class Type, class... Args>
    Type*
    Builder::reserve(Args... args)
    {
        void* addr = alloc->reserve(
            sizeof(Type),
            alignof(Type)
        );

        return new((Type*) addr) Type(args...);
    }

    template <class Type>
    bool
    Builder::reclaim(Type* addr)
    {
        return alloc->reclaim(addr);
    }
} // pax
