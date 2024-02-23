#include <light/Base/Buffer.hpp>

namespace light
{
    template <class Type, u64 Size>
    Type&
    Buffer<Type, Size>::operator[](u64 index)
    {
        return data[index];
    }

    template <class Type, u64 Size>
    const Type&
    Buffer<Type, Size>::operator[](u64 index) const
    {
        return data[index];
    }
} // light
