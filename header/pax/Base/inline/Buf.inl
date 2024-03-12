#include <pax/Base/Buf.hpp>

namespace pax
{
    template <class Type, u64 Size>
    Type&
    Buf<Type, Size>::operator[](u64 index)
    {
        #if PAX_TEST_BOUNDS
            if ( index >= SIZE )
                pax_panic("test-bounds", "index, %lu exceeds %lu", index, SIZE);
        #endif

        return data[index];
    }

    template <class Type, u64 Size>
    const Type&
    Buf<Type, Size>::operator[](u64 index) const
    {
        #if PAX_TEST_BOUNDS
            if ( index >= SIZE )
                pax_panic("test-bounds", "index, %lu exceeds %lu", index, SIZE);
        #endif

        return data[index];
    }
} // pax
