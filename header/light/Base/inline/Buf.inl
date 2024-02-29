#include <light/Base/Buf.hpp>

namespace light
{
    template <class Type, u64 Size>
    Type&
    Buf<Type, Size>::operator[](u64 index)
    {
        #if LIGHT_TEST_BOUNDS
            if ( index >= SIZE )
                light_panic("test-bounds", "index, %lu exceeds %lu", index, SIZE);
        #endif

        return data[index];
    }

    template <class Type, u64 Size>
    const Type&
    Buf<Type, Size>::operator[](u64 index) const
    {
        #if LIGHT_TEST_BOUNDS
            if ( index >= SIZE )
                light_panic("test-bounds", "index, %lu exceeds %lu", index, SIZE);
        #endif

        return data[index];
    }
} // light
