#include <light/Base/Vec.hpp>

namespace light
{
    template <class Type, u32 Size>
    template <class Other>
    Vec<Type, Size>
    Vec<Type, Size>::from(const Vec<Other, Size>& other)
    {
        Vec<Type, Size> res;

        for ( u32 i = 0; i < SIZE; i += 1u )
            res.data[i] = other.data[i];

        return res;
    }

    template <class Type, u32 Size>
    Type
    Vec<Type, Size>::magnitude() const
    {
        Type res = 0;

        for ( u32 i = 0; i < SIZE; i += 1u )
            res += data[i] * data[i];

        return sqrt(res);
    }

    template <class Type, u32 Size>
    template <class Other>
    Vec<Type, Size>
    Vec<Type, Size>::operator+(const Vec<Other, Size>& other) const
    {
        Vec<Type, Size> res;

        for ( u32 i = 0; i < SIZE; i += 1u )
            res.data[i] = data[i] + other.data[i];

        return res;
    }

    template <class Type, u32 Size>
    template <class Other>
    Vec<Type, Size>
    Vec<Type, Size>::operator+(Other other) const
    {
        Vec<Type, Size> res;

        for ( u32 i = 0; i < SIZE; i += 1u )
            res.data[i] = data[i] + other;

        return res;
    }

    template <class Type, u32 Size>
    template <class Other>
    Vec<Type, Size>&
    Vec<Type, Size>::operator+=(const Vec<Other, Size>& other)
    {
        for ( u32 i = 0; i < SIZE; i += 1u )
            data[i] += other.data[i];

        return *this;
    }

    template <class Type, u32 Size>
    template <class Other>
    Vec<Type, Size>&
    Vec<Type, Size>::operator+=(Other other)
    {
        for ( u32 i = 0; i < SIZE; i += 1u )
            data[i] += other;

        return *this;
    }

    template <class Type, u32 Size>
    template <class Other>
    Vec<Type, Size>
    Vec<Type, Size>::operator-(const Vec<Other, Size>& other) const
    {
        Vec<Type, Size> res;

        for ( u32 i = 0; i < SIZE; i += 1u )
            res.data[i] = data[i] - other.data[i];

        return res;
    }

    template <class Type, u32 Size>
    template <class Other>
    Vec<Type, Size>
    Vec<Type, Size>::operator-(Other other) const
    {
        Vec<Type, Size> res;

        for ( u32 i = 0; i < SIZE; i += 1u )
            res.data[i] = data[i] - other;

        return res;
    }

    template <class Type, u32 Size>
    template <class Other>
    Vec<Type, Size>&
    Vec<Type, Size>::operator-=(const Vec<Other, Size>& other)
    {
        for ( u32 i = 0; i < SIZE; i += 1u )
            data[i] -= other.data[i];

        return *this;
    }

    template <class Type, u32 Size>
    template <class Other>
    Vec<Type, Size>&
    Vec<Type, Size>::operator-=(Other other)
    {
        for ( u32 i = 0; i < SIZE; i += 1u )
            data[i] -= other;

        return *this;
    }

    template <class Type, u32 Size>
    template <class Other>
    Vec<Type, Size>
    Vec<Type, Size>::operator*(const Vec<Other, Size>& other) const
    {
        Vec<Type, Size> res;

        for ( u32 i = 0; i < SIZE; i += 1u )
            res.data[i] = data[i] * other.data[i];

        return res;
    }

    template <class Type, u32 Size>
    template <class Other>
    Vec<Type, Size>
    Vec<Type, Size>::operator*(Other other) const
    {
        Vec<Type, Size> res;

        for ( u32 i = 0; i < SIZE; i += 1u )
            res.data[i] = data[i] * other;

        return res;
    }

    template <class Type, u32 Size>
    template <class Other>
    Vec<Type, Size>&
    Vec<Type, Size>::operator*=(const Vec<Other, Size>& other)
    {
        for ( u32 i = 0; i < SIZE; i += 1u )
            data[i] *= other.data[i];

        return *this;
    }

    template <class Type, u32 Size>
    template <class Other>
    Vec<Type, Size>&
    Vec<Type, Size>::operator*=(Other other)
    {
        for ( u32 i = 0; i < SIZE; i += 1u )
            data[i] *= other;

        return *this;
    }

    template <class Type, u32 Size>
    template <class Other>
    Vec<Type, Size>
    Vec<Type, Size>::operator/(const Vec<Other, Size>& other) const
    {
        Vec<Type, Size> res;

        for ( u32 i = 0; i < SIZE; i += 1u )
            res.data[i] = data[i] / other.data[i];

        return res;
    }

    template <class Type, u32 Size>
    template <class Other>
    Vec<Type, Size>
    Vec<Type, Size>::operator/(Other other) const
    {
        Vec<Type, Size> res;

        for ( u32 i = 0; i < SIZE; i += 1u )
            res.data[i] = data[i] / other;

        return res;
    }

    template <class Type, u32 Size>
    template <class Other>
    Vec<Type, Size>&
    Vec<Type, Size>::operator/=(const Vec<Other, Size>& other)
    {
        for ( u32 i = 0; i < SIZE; i += 1u )
            data[i] /= other.data[i];

        return *this;
    }

    template <class Type, u32 Size>
    template <class Other>
    Vec<Type, Size>&
    Vec<Type, Size>::operator/=(Other other)
    {
        for ( u32 i = 0; i < SIZE; i += 1u )
            data[i] /= other;

        return *this;
    }

    template <class Type, u32 Size>
    Type&
    Vec<Type, Size>::operator[](u32 index)
    {
        return data[index];
    }

    template <class Type, u32 Size>
    const Type&
    Vec<Type, Size>::operator[](u32 index) const
    {
        return data[index];
    }

    template <class Type, u32 Size>
    bool
    Vec<Type, Size>::operator==(const Vec<Type, Size>& other) const
    {
        for ( u32 i = 0; i < SIZE; i += 1u ) {
            if ( data[i] != other.data[i] )
                return false;
        }

        return true;
    }

    template <class Type, u32 Size>
    bool
    Vec<Type, Size>::operator!=(const Vec<Type, Size>& other) const
    {
        for ( u32 i = 0; i < SIZE; i += 1u ) {
            if ( data[i] != other.data[i] )
                return true;
        }

        return false;
    }
} // light
