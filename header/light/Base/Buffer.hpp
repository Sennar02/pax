#ifndef LIGHT_BASE_BUFFER_HPP
#define LIGHT_BASE_BUFFER_HPP

#include <light/Base/define.hpp>

namespace light
{
    template <class Type, u32 Size>
    struct Buffer
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

#include <light/Base/inline/Buffer.inl>

#endif // LIGHT_BASE_BUFFER_HPP
