#include <light/Base/Buf.hpp>

namespace light
{
    template <class Type, u64 Size>
    Type&
    Buf<Type, Size>::operator[](u64 index)
    {
        return data[index];
    }

    template <class Type, u64 Size>
    const Type&
    Buf<Type, Size>::operator[](u64 index) const
    {
        return data[index];
    }
} // light
