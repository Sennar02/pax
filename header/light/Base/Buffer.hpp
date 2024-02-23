#ifndef LIGHT_BASE_BUFFER_HPP
#define LIGHT_BASE_BUFFER_HPP

#include <light/Base/define.hpp>

namespace light
{
    template <class Type, u64 Size>
    struct Buffer
    {
    public:
        static const u64 LEN_TYPE =
            sizeof(Type);

        /**
         * Number of elements.
         */
        static const u64 SIZE = Size;

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
        operator[](u64 index);

        /**
         * Subscript operator, doesn't test bounds.
         */
        const Type&
        operator[](u64 index) const;
    };
} // light

#include <light/Base/inline/Buffer.inl>

#endif // LIGHT_BASE_BUFFER_HPP
