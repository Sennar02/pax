#include <light/Base/Buffer.hpp>

namespace light
{
    template <class Type, u32 Size>
    Type&
    Buffer<Type, Size>::operator[](u32 index)
    {
        return data[index];
    }

    template <class Type, u32 Size>
    const Type&
    Buffer<Type, Size>::operator[](u32 index) const
    {
        return data[index];
    }
} // light
