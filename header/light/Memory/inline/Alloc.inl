#include <light/Memory/Alloc.hpp>
#include <new>

namespace light
{
    template <class Type, class... Args>
    Type*
    reserve(Alloc& alloc, Args... args)
    {
        Type* res = (Type*) alloc.reserve(
            sizeof(Type), alignof(Type)
        );

        if ( res != 0 )
           new (res) Type(args...);

        return res;
    }
} // light
