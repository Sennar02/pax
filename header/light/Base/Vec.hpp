#ifndef LIGHT_BASE_VEC_HPP
#define LIGHT_BASE_VEC_HPP

#include <light/Base/define.hpp>

namespace light
{
    template <class Type, u64 Size>
    struct Vec
    {
    public:
        /**
         * Number of elements.
         */
        static const u64 SIZE = Size;

    public:
        /**
         * Static array of elements.
         */
        Type data[Size];

    public:
        /**
         * Creates a vector from one of another type.
         */
        template <class Other>
        void
        from(Vec<Other, Size> other);

        /**
         * Calculates the magnitude of the vector,
         * for example on a vector of size two
         * computes the square root of a^2 + b^2.
         */
        Type
        magnitude() const;

        /**
         * Subscript operator, doesn't test bounds.
         */
        Type&
        operator[](u64 index);

        /**
         * Subscript operator, doesn't test bounds.
         */
        const Type&
        operator[](u64 index) const;

        /**
         * Tests if two vectors are equal.
         */
        bool
        operator==(Vec<Type, Size> other) const;

        /**
         * Tests if two vectors are different.
         */
        bool
        operator!=(Vec<Type, Size> other) const;
    };

    /**
     * Performs the addition of two vectors.
     */
    template <class Type, class Other, u64 Size>
    Vec<Type, Size>
    vec_add(Vec<Type, Size> a, Vec<Other, Size> b);

    /**
     * Performs the addition of a vector and a scalar.
     */
    template <class Type, class Other, u64 Size>
    Vec<Type, Size>
    vec_sadd(Vec<Type, Size> a, Other b);

    /**
     * Performs the subtraction of two vectors.
     */
    template <class Type, class Other, u64 Size>
    Vec<Type, Size>
    vec_sub(Vec<Type, Size> a, Vec<Other, Size> b);

    /**
     * Performs the subtraction of a vector and a scalar.
     */
    template <class Type, class Other, u64 Size>
    Vec<Type, Size>
    vec_ssub(Vec<Type, Size> a, Other b);

    /**
     * Performs the scaling multiplication of two vectors.
     */
    template <class Type, class Other, u64 Size>
    Vec<Type, Size>
    vec_mul_scale(Vec<Type, Size> a, Vec<Other, Size> b);

    /**
     * Performs the scaling multiplication of a vector and a scalar.
     */
    template <class Type, class Other, u64 Size>
    Vec<Type, Size>
    vec_smul_scale(Vec<Type, Size> a, Other b);

    /**
     * Performs the scaling division of two vectors.
     */
    template <class Type, class Other, u64 Size>
    Vec<Type, Size>
    vec_div_scale(Vec<Type, Size> a, Vec<Other, Size> b);

    /**
     * Performs the scaling division of a vector and a scalar.
     */
    template <class Type, class Other, u64 Size>
    Vec<Type, Size>
    vec_sdiv_scale(Vec<Type, Size> a, Other b);
} // light

#include <light/Base/inline/Vec.inl>

#endif // LIGHT_BASE_VEC_HPP
