#ifndef LIGHT_BASE_ARRAY_HPP
#define LIGHT_BASE_ARRAY_HPP

#include <light/Base/define.hpp>

namespace light
{
    template <class Type, u32 Size>
    struct Array
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
        Type data[Size] = {0};

    public:
        /**
         * Subscript operator, doesn't test bounds.
         */
        Type&
        operator[](u32 index);

        /**
         * Subscript operator, doesn't test bounds.
         */
        const Type&
        operator[](u32 index) const;
    };
} // light

#include <light/Base/inline/Array.inl>

#endif // LIGHT_BASE_ARRAY_HPP
