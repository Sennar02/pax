#include <light/Base/Vec.hpp>

namespace light
{
    template <class Type, u64 Size>
    template <class Other>
    void
    Vec<Type, Size>::from(Vec<Other, Size> other)
    {
        for ( u64 i = 0; i < SIZE; i += 1u )
            data[i] = other.data[i];
    }

    template <class Type, u64 Size>
    Type
    Vec<Type, Size>::magnitude() const
    {
        Type res = 0;

        for ( u64 i = 0; i < SIZE; i += 1u )
            res += data[i] * data[i];

        return sqrt(res);
    }

    template <class Type, u64 Size>
    template <class Other>
    Vec<Type, Size>
    Vec<Type, Size>::operator+(Vec<Other, Size> other) const
    {
        Vec<Type, Size> res;

        for ( u64 i = 0; i < SIZE; i += 1u )
            res[i] = data[i] + other.data[i];

        return res;
    }

    template <class Type, u64 Size>
    template <class Other>
    Vec<Type, Size>
    Vec<Type, Size>::operator+(Other other) const
    {
        Vec<Type, Size> res;

        for ( u64 i = 0; i < SIZE; i += 1u )
            res[i] = data[i] + other;

        return res;
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
        Vec<Type, Size> res;

        for ( u64 i = 0; i < SIZE; i += 1u )
            res[i] = data[i] - other.data[i];

        return res;
    }

    template <class Type, u64 Size>
    template <class Other>
    Vec<Type, Size>
    Vec<Type, Size>::operator-(Other other) const
    {
        Vec<Type, Size> res;

        for ( u64 i = 0; i < SIZE; i += 1u )
            res[i] = data[i] - other;

        return res;
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
        Vec<Type, Size> res;

        for ( u64 i = 0; i < SIZE; i += 1u )
            res[i] = data[i] * other.data[i];

        return res;
    }

    template <class Type, u64 Size>
    template <class Other>
    Vec<Type, Size>
    Vec<Type, Size>::operator*(Other other) const
    {
        Vec<Type, Size> res;

        for ( u64 i = 0; i < SIZE; i += 1u )
            res[i] = data[i] * other;

        return res;
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
        Vec<Type, Size> res;

        for ( u64 i = 0; i < SIZE; i += 1u )
            res[i] = data[i] / other.data[i];

        return res;
    }

    template <class Type, u64 Size>
    template <class Other>
    Vec<Type, Size>
    Vec<Type, Size>::operator/(Other other) const
    {
        Vec<Type, Size> res;

        for ( u64 i = 0; i < SIZE; i += 1u )
            res[i] = data[i] / other;

        return res;
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
        #if LIGHT_TEST_BOUNDS
            if ( index >= SIZE )
                light_panic("test-bounds", "index %lu exceeds %lu", index, SIZE);
        #endif

        return data[index];
    }

    template <class Type, u64 Size>
    const Type&
    Vec<Type, Size>::operator[](u64 index) const
    {
        #if LIGHT_TEST_BOUNDS
            if ( index >= SIZE )
                light_panic("test-bounds", "index %lu exceeds %lu", index, SIZE);
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
} // light
