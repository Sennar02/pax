#ifndef LIGHT_BASE_VEC_HPP
#define LIGHT_BASE_VEC_HPP

#include <light/Base/define.hpp>

namespace light
{
    template <class Type, u32 Size>
    struct Vec
    {
    public:
        /**
         * Number of elements.
         */
        static const u32 SIZE = Size;

    public:
        /**
         * Elements.
         */
        Type data[Size];

    public:
        template <class Other>
        static Vec<Type, Size>
        from(const Vec<Other, Size>& other);

        /**
         * Calculates the magnitude of the vector,
         * for example on a vector of size two
         * computes the square root of a^2 + b^2.
         */
        Type
        magnitude() const;

        template <class Other>
        Vec<Type, Size>
        operator+(const Vec<Other, Size>& other) const;

        template <class Other>
        Vec<Type, Size>
        operator+(Other other) const;

        template <class Other>
        Vec<Type, Size>&
        operator+=(const Vec<Other, Size>& other);

        template <class Other>
        Vec<Type, Size>&
        operator+=(Other other);

        template <class Other>
        Vec<Type, Size>
        operator-(const Vec<Other, Size>& other) const;

        template <class Other>
        Vec<Type, Size>
        operator-(Other other) const;

        template <class Other>
        Vec<Type, Size>&
        operator-=(const Vec<Other, Size>& other);

        template <class Other>
        Vec<Type, Size>&
        operator-=(Other other);

        template <class Other>
        Vec<Type, Size>
        operator*(const Vec<Other, Size>& other) const;

        template <class Other>
        Vec<Type, Size>
        operator*(Other other) const;

        template <class Other>
        Vec<Type, Size>&
        operator*=(const Vec<Other, Size>& other);

        template <class Other>
        Vec<Type, Size>&
        operator*=(Other other);

        template <class Other>
        Vec<Type, Size>
        operator/(const Vec<Other, Size>& other) const;

        template <class Other>
        Vec<Type, Size>
        operator/(Other other) const;

        template <class Other>
        Vec<Type, Size>&
        operator/=(const Vec<Other, Size>& other);

        template <class Other>
        Vec<Type, Size>&
        operator/=(Other other);

        Type&
        operator[](u32 index);

        const Type&
        operator[](u32 index) const;

        bool
        operator==(const Vec<Type, Size>& other) const;

        bool
        operator!=(const Vec<Type, Size>& other) const;
    };
} // light

#include <light/Base/inline/Vec.inl>

#endif // LIGHT_BASE_VEC_HPP
