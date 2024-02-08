#include <light/Base/Vec.hpp>

namespace light
{
    template <class Type, u32 Size>
    Type
    Vec<Type, Size>::magnitude() const
    {
        Type res = 0;

        for ( u32 i = 0; i < SIZE; i++ )
            res += data[i] * data[i];

        return sqrt(res);
    }

    template <class Type, u32 Size>
    Vec<Type, Size>
    Vec<Type, Size>::operator+(const Vec<Type, Size>& other) const
    {
        Vec<Type, Size> res;

        for ( u32 i = 0; i < SIZE; i++ )
            res.data[i] = data[i] + other.data[i];

        return res;
    }

    template <class Type, u32 Size>
    Vec<Type, Size>
    Vec<Type, Size>::operator+(Type other) const
    {
        Vec<Type, Size> res;

        for ( u32 i = 0; i < SIZE; i++ )
            res.data[i] = data[i] + other;

        return res;
    }

    template <class Type, u32 Size>
    Vec<Type, Size>&
    Vec<Type, Size>::operator+=(const Vec<Type, Size>& other)
    {
        for ( u32 i = 0; i < SIZE; i++ )
            data[i] += other.data[i];

        return *this;
    }

    template <class Type, u32 Size>
    Vec<Type, Size>&
    Vec<Type, Size>::operator+=(Type other)
    {
        for ( u32 i = 0; i < SIZE; i++ )
            data[i] += other;

        return *this;
    }

    template <class Type, u32 Size>
    Vec<Type, Size>
    Vec<Type, Size>::operator-(const Vec<Type, Size>& other) const
    {
        Vec<Type, Size> res;

        for ( u32 i = 0; i < SIZE; i++ )
            res.data[i] = data[i] - other.data[i];

        return res;
    }

    template <class Type, u32 Size>
    Vec<Type, Size>
    Vec<Type, Size>::operator-(Type other) const
    {
        Vec<Type, Size> res;

        for ( u32 i = 0; i < SIZE; i++ )
            res.data[i] = data[i] - other;

        return res;
    }

    template <class Type, u32 Size>
    Vec<Type, Size>&
    Vec<Type, Size>::operator-=(const Vec<Type, Size>& other)
    {
        for ( u32 i = 0; i < SIZE; i++ )
            data[i] -= other.data[i];

        return *this;
    }

    template <class Type, u32 Size>
    Vec<Type, Size>&
    Vec<Type, Size>::operator-=(Type other)
    {
        for ( u32 i = 0; i < SIZE; i++ )
            data[i] -= other;

        return *this;
    }

    template <class Type, u32 Size>
    Vec<Type, Size>
    Vec<Type, Size>::operator*(const Vec<Type, Size>& other) const
    {
        Vec<Type, Size> res;

        for ( u32 i = 0; i < SIZE; i++ )
            res.data[i] = data[i] * other.data[i];

        return res;
    }

    template <class Type, u32 Size>
    Vec<Type, Size>
    Vec<Type, Size>::operator*(Type other) const
    {
        Vec<Type, Size> res;

        for ( u32 i = 0; i < SIZE; i++ )
            res.data[i] = data[i] * other;

        return res;
    }

    template <class Type, u32 Size>
    Vec<Type, Size>&
    Vec<Type, Size>::operator*=(const Vec<Type, Size>& other)
    {
        for ( u32 i = 0; i < SIZE; i++ )
            data[i] *= other.data[i];

        return *this;
    }

    template <class Type, u32 Size>
    Vec<Type, Size>&
    Vec<Type, Size>::operator*=(Type other)
    {
        for ( u32 i = 0; i < SIZE; i++ )
            data[i] *= other;

        return *this;
    }

    template <class Type, u32 Size>
    Vec<Type, Size>
    Vec<Type, Size>::operator/(const Vec<Type, Size>& other) const
    {
        Vec<Type, Size> res;

        for ( u32 i = 0; i < SIZE; i++ )
            res.data[i] = data[i] / other.data[i];

        return res;
    }

    template <class Type, u32 Size>
    Vec<Type, Size>
    Vec<Type, Size>::operator/(Type other) const
    {
        Vec<Type, Size> res;

        for ( u32 i = 0; i < SIZE; i++ )
            res.data[i] = data[i] / other;

        return res;
    }

    template <class Type, u32 Size>
    Vec<Type, Size>&
    Vec<Type, Size>::operator/=(const Vec<Type, Size>& other)
    {
        for ( u32 i = 0; i < SIZE; i++ )
            data[i] /= other.data[i];

        return *this;
    }

    template <class Type, u32 Size>
    Vec<Type, Size>&
    Vec<Type, Size>::operator/=(Type other)
    {
        for ( u32 i = 0; i < SIZE; i++ )
            data[i] /= other;

        return *this;
    }

    template <class Type, u32 Size>
    bool
    Vec<Type, Size>::operator==(const Vec<Type, Size>& other) const
    {
        for ( u32 i = 0; i < SIZE; i++ ) {
            if ( data[i] != other.data[i] )
                return false;
        }

        return true;
    }

    template <class Type, u32 Size>
    bool
    Vec<Type, Size>::operator!=(const Vec<Type, Size>& other) const
    {
        for ( u32 i = 0; i < SIZE; i++ ) {
            if ( data[i] != other.data[i] )
                return true;
        }

        return false;
    }
} // light
