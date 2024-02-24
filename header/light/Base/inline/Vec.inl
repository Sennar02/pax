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
    Type&
    Vec<Type, Size>::operator[](u64 index)
    {
        return data[index];
    }

    template <class Type, u64 Size>
    const Type&
    Vec<Type, Size>::operator[](u64 index) const
    {
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

    template <class Type, class Other, u64 Size>
    Vec<Type, Size>
    vec_add(Vec<Type, Size> a, Vec<Other, Size> b)
    {
        Vec<Type, Size> res;

        for ( u64 i = 0; i < res.SIZE; i += 1u )
            res.data[i] = a.data[i] + b.data[i];

        return res;
    }

    template <class Type, class Other, u64 Size>
    Vec<Type, Size>
    vec_sadd(Vec<Type, Size> a, Other b)
    {
        Vec<Type, Size> res;

        for ( u64 i = 0; i < res.SIZE; i += 1u )
            res.data[i] = a.data[i] + b;

        return res;
    }

    template <class Type, class Other, u64 Size>
    Vec<Type, Size>
    vec_sub(Vec<Type, Size> a, Vec<Other, Size> b)
    {
        Vec<Type, Size> res;

        for ( u64 i = 0; i < res.SIZE; i += 1u )
            res.data[i] = a.data[i] - b.data[i];

        return res;
    }

    template <class Type, class Other, u64 Size>
    Vec<Type, Size>
    vec_ssub(Vec<Type, Size> a, Other b)
    {
        Vec<Type, Size> res;

        for ( u64 i = 0; i < res.SIZE; i += 1u )
            res.data[i] = a.data[i] - b;

        return res;
    }

    template <class Type, class Other, u64 Size>
    Vec<Type, Size>
    vec_mul_scale(Vec<Type, Size> a, Vec<Other, Size> b)
    {
        Vec<Type, Size> res;

        for ( u64 i = 0; i < res.SIZE; i += 1u )
            res.data[i] = a.data[i] * b.data[i];

        return res;
    }

    template <class Type, class Other, u64 Size>
    Vec<Type, Size>
    vec_smul_scale(Vec<Type, Size> a, Other b)
    {
        Vec<Type, Size> res;

        for ( u64 i = 0; i < res.SIZE; i += 1u )
            res.data[i] = a.data[i] * b;

        return res;
    }

    template <class Type, class Other, u64 Size>
    Vec<Type, Size>
    vec_div_scale(Vec<Type, Size> a, Vec<Other, Size> b)
    {
        Vec<Type, Size> res;

        for ( u64 i = 0; i < res.SIZE; i += 1u )
            res.data[i] = a.data[i] / b.data[i];

        return res;
    }

    template <class Type, class Other, u64 Size>
    Vec<Type, Size>
    vec_sdiv_scale(Vec<Type, Size> a, Other b)
    {
        Vec<Type, Size> res;

        for ( u64 i = 0; i < res.SIZE; i += 1u )
            res.data[i] = a.data[i] / b;

        return res;
    }
} // light
