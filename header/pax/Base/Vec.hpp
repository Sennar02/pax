#ifndef PAX_BASE_VEC_HPP
#define PAX_BASE_VEC_HPP

#include <pax/Base/define.hpp>
#include <pax/Base/util.hpp>

namespace pax
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
         * Constructor which populatea the vector from one of another type.
         */
        template <class Other>
        static Vec<Type, Size>
        build(Vec<Other, Size> other);

        /**
         * Calculates the magnitude of the vector,
         * for example on a vector of size two
         * computes the square root of a^2 + b^2.
         */
        Type
        magnitude() const;

        /**
         * Performs the addition of two vectors.
         */
        template <class Other>
        Vec<Type, Size>
        operator+(Vec<Other, Size> other) const;

        /**
         * Performs the addition of a vector and a scalar.
        */
        template <class Other>
        Vec<Type, Size>
        operator+(Other other) const;

        /**
         * Performs the addition on the vector with another.
         */
        template <class Other>
        Vec<Type, Size>&
        operator+=(Vec<Other, Size> other);

        /**
         * Performs the addition on the vector with a scalar.
        */
        template <class Other>
        Vec<Type, Size>&
        operator+=(Other other);

        /**
         * Performs the subtraction of two vectors.
         */
        template <class Other>
        Vec<Type, Size>
        operator-(Vec<Other, Size> other) const;

        /**
         * Performs the subtraction of a vector and a scalar.
         */
        template <class Other>
        Vec<Type, Size>
        operator-(Other other) const;

        /**
         * Performs the subtraction on the vector with another.
         */
        template <class Other>
        Vec<Type, Size>&
        operator-=(Vec<Other, Size> other);

        /**
         * Performs the subtraction on the vector with a scalar.
        */
        template <class Other>
        Vec<Type, Size>&
        operator-=(Other other);

        /**
         * Performs the Hadamard multiplication of two vectors.
         */
        template <class Other>
        Vec<Type, Size>
        operator*(Vec<Other, Size> other) const;

        /**
         * Performs the Hadamard multiplication of a vector and a scalar.
        */
        template <class Other>
        Vec<Type, Size>
        operator*(Other other) const;

        /**
         * Performs the Hadamard multiplication on the vector with another.
         */
        template <class Other>
        Vec<Type, Size>&
        operator*=(Vec<Other, Size> other);

        /**
         * Performs the Hadamard multiplication on the vector with a scalar.
         */
        template <class Other>
        Vec<Type, Size>&
        operator*=(Other other);

        /**
         * Performs the Hadamard division of two vectors.
         */
        template <class Other>
        Vec<Type, Size>
        operator/(Vec<Other, Size> other) const;

        /**
         * Performs the Hadamard division of a vector and a scalar.
         */
        template <class Other>
        Vec<Type, Size>
        operator/(Other other) const;

        /**
         * Performs the Hadamard division on the vector with another.
         */
        template <class Other>
        Vec<Type, Size>&
        operator/=(Vec<Other, Size> other);

        /**
         * Performs the Hadamard division on the vector with a scalar.
         */
        template <class Other>
        Vec<Type, Size>&
        operator/=(Other other);

        /**
         * Subscript operator.
         */
        Type&
        operator[](u64 index);

        /**
         * Subscript operator.
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
} // pax

#include <pax/Base/inline/Vec.inl>

#endif // PAX_BASE_VEC_HPP
