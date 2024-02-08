#ifndef LIGHT_BASE_VEC_HPP
#define LIGHT_BASE_VEC_HPP

#include <light/Base/define.hpp>

namespace light
{
    template <class Type, u32 Size>
    struct Vec
    {
    public:
        // Number of elements.
        static const u32 SIZE = Size;

        // Array of elements.
        Type data[Size];

    public:
        Type
        strength() const;

        Vec<Type, Size>
        operator+(const Vec<Type, Size>& other) const;

        Vec<Type, Size>
        operator+(Type other) const;

        Vec<Type, Size>&
        operator+=(const Vec<Type, Size>& other);

        Vec<Type, Size>&
        operator+=(Type other);

        Vec<Type, Size>
        operator-(const Vec<Type, Size>& other) const;

        Vec<Type, Size>
        operator-(Type other) const;

        Vec<Type, Size>&
        operator-=(const Vec<Type, Size>& other);

        Vec<Type, Size>&
        operator-=(Type other);

        Vec<Type, Size>
        operator*(const Vec<Type, Size>& other) const;

        Vec<Type, Size>
        operator*(Type other) const;

        Vec<Type, Size>&
        operator*=(const Vec<Type, Size>& other);

        Vec<Type, Size>&
        operator*=(Type other);

        Vec<Type, Size>
        operator/(const Vec<Type, Size>& other) const;

        Vec<Type, Size>
        operator/(Type other) const;

        Vec<Type, Size>&
        operator/=(const Vec<Type, Size>& other);

        Vec<Type, Size>&
        operator/=(Type other);

        bool
        operator==(const Vec<Type, Size>& other) const;

        bool
        operator!=(const Vec<Type, Size>& other) const;
    };
} // light

#include <light/Base/inline/Vec.inl>

#endif // LIGHT_BASE_VEC_HPP
