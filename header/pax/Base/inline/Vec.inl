#include <pax/Base/Vec.hpp>

namespace pax
{
    template <class Type, u64 Size>
    template <class Other>
    Vec<Type, Size>
    Vec<Type, Size>::build(Vec<Other, Size> other)
    {
        Vec<Type, Size> reslt;

        for ( u64 i = 0; i < SIZE; i += 1u )
            reslt.data[i] = other.data[i];

        return reslt;
    }

    template <class Type, u64 Size>
    Type
    Vec<Type, Size>::magnitude() const
    {
        Type reslt = 0;

        for ( u64 i = 0; i < SIZE; i += 1u )
            reslt += data[i] * data[i];

        return sqrt(reslt);
    }

    template <class Type, u64 Size>
    template <class Other>
    Vec<Type, Size>
    Vec<Type, Size>::operator+(Vec<Other, Size> other) const
    {
        Vec<Type, Size> reslt;

        for ( u64 i = 0; i < SIZE; i += 1u )
            reslt[i] = data[i] + other.data[i];

        return reslt;
    }

    template <class Type, u64 Size>
    template <class Other>
    Vec<Type, Size>
    Vec<Type, Size>::operator+(Other other) const
    {
        Vec<Type, Size> reslt;

        for ( u64 i = 0; i < SIZE; i += 1u )
            reslt[i] = data[i] + other;

        return reslt;
    }

    template <class Type, u64 Size>
    template <class Other>
    Vec<Type, Size>&
    Vec<Type, Size>::operator+=(Vec<Other, Size> other)
    {
        for ( u64 i = 0; i < SIZE; i += 1u )
            data[i] += other.data[i];

        return *this;
    }

    template <class Type, u64 Size>
    template <class Other>
    Vec<Type, Size>&
    Vec<Type, Size>::operator+=(Other other)
    {
        for ( u64 i = 0; i < SIZE; i += 1u )
            data[i] += other;

        return *this;
    }

    template <class Type, u64 Size>
    template <class Other>
    Vec<Type, Size>
    Vec<Type, Size>::operator-(Vec<Other, Size> other) const
    {
        Vec<Type, Size> reslt;

        for ( u64 i = 0; i < SIZE; i += 1u )
            reslt[i] = data[i] - other.data[i];

        return reslt;
    }

    template <class Type, u64 Size>
    template <class Other>
    Vec<Type, Size>
    Vec<Type, Size>::operator-(Other other) const
    {
        Vec<Type, Size> reslt;

        for ( u64 i = 0; i < SIZE; i += 1u )
            reslt[i] = data[i] - other;

        return reslt;
    }

    template <class Type, u64 Size>
    template <class Other>
    Vec<Type, Size>&
    Vec<Type, Size>::operator-=(Vec<Other, Size> other)
    {
        for ( u64 i = 0; i < SIZE; i += 1u )
            data[i] -= other.data[i];

        return *this;
    }

    template <class Type, u64 Size>
    template <class Other>
    Vec<Type, Size>&
    Vec<Type, Size>::operator-=(Other other)
    {
        for ( u64 i = 0; i < SIZE; i += 1u )
            data[i] -= other;

        return *this;
    }

    template <class Type, u64 Size>
    template <class Other>
    Vec<Type, Size>
    Vec<Type, Size>::operator*(Vec<Other, Size> other) const
    {
        Vec<Type, Size> reslt;

        for ( u64 i = 0; i < SIZE; i += 1u )
            reslt[i] = data[i] * other.data[i];

        return reslt;
    }

    template <class Type, u64 Size>
    template <class Other>
    Vec<Type, Size>
    Vec<Type, Size>::operator*(Other other) const
    {
        Vec<Type, Size> reslt;

        for ( u64 i = 0; i < SIZE; i += 1u )
            reslt[i] = data[i] * other;

        return reslt;
    }

    template <class Type, u64 Size>
    template <class Other>
    Vec<Type, Size>&
    Vec<Type, Size>::operator*=(Vec<Other, Size> other)
    {
        for ( u64 i = 0; i < SIZE; i += 1u )
            data[i] *= other.data[i];

        return *this;
    }

    template <class Type, u64 Size>
    template <class Other>
    Vec<Type, Size>&
    Vec<Type, Size>::operator*=(Other other)
    {
        for ( u64 i = 0; i < SIZE; i += 1u )
            data[i] *= other;

        return *this;
    }

    template <class Type, u64 Size>
    template <class Other>
    Vec<Type, Size>
    Vec<Type, Size>::operator/(Vec<Other, Size> other) const
    {
        Vec<Type, Size> reslt;

        for ( u64 i = 0; i < SIZE; i += 1u )
            reslt[i] = data[i] / other.data[i];

        return reslt;
    }

    template <class Type, u64 Size>
    template <class Other>
    Vec<Type, Size>
    Vec<Type, Size>::operator/(Other other) const
    {
        Vec<Type, Size> reslt;

        for ( u64 i = 0; i < SIZE; i += 1u )
            reslt[i] = data[i] / other;

        return reslt;
    }

    template <class Type, u64 Size>
    template <class Other>
    Vec<Type, Size>&
    Vec<Type, Size>::operator/=(Vec<Other, Size> other)
    {
        for ( u64 i = 0; i < SIZE; i += 1u )
            data[i] /= other.data[i];

        return *this;
    }

    template <class Type, u64 Size>
    template <class Other>
    Vec<Type, Size>&
    Vec<Type, Size>::operator/=(Other other)
    {
        for ( u64 i = 0; i < SIZE; i += 1u )
            data[i] /= other;

        return *this;
    }

    template <class Type, u64 Size>
    Type&
    Vec<Type, Size>::operator[](u64 index)
    {
        #if PAX_TEST_BOUNDS
            if ( index >= SIZE )
                pax_panic("test-bounds", "index %lu exceeds %lu", index, SIZE);
        #endif

        return data[index];
    }

    template <class Type, u64 Size>
    const Type&
    Vec<Type, Size>::operator[](u64 index) const
    {
        #if PAX_TEST_BOUNDS
            if ( index >= SIZE )
                pax_panic("test-bounds", "index %lu exceeds %lu", index, SIZE);
        #endif

        return data[index];
    }

    template <class Type, u64 Size>
    bool
    Vec<Type, Size>::operator==(Vec<Type, Size> other) const
    {
        for ( u64 i = 0; i < SIZE; i += 1u ) {
            if ( data[i] != other.data[i] )
                return false;
        }

        return true;
    }

    template <class Type, u64 Size>
    bool
    Vec<Type, Size>::operator!=(Vec<Type, Size> other) const
    {
        for ( u64 i = 0; i < SIZE; i += 1u ) {
            if ( data[i] != other.data[i] )
                return true;
        }

        return false;
    }
} // pax
