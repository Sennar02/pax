#include <light/Base/Array.hpp>

namespace light
{
    template <class Type, u32 Size>
    Type&
    Array<Type, Size>::operator[](u32 index)
    {
        return data[index];
    }

    template <class Type, u32 Size>
    const Type&
    Array<Type, Size>::operator[](u32 index) const
    {
        return data[index];
    }
} // light
