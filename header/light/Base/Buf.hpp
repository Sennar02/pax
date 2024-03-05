#ifndef LIGHT_BASE_BUF_HPP
#define LIGHT_BASE_BUF_HPP

#include <light/Base/define.hpp>
#include <light/Base/util.hpp>

namespace light
{
    template <class Type, u64 Size>
    struct Buf
    {
    public:
        /**
         * Size in bytes of the type.
         */
        static const u64 LEN_TYPE =
            sizeof(Type);

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
         * Subscript operator.
         */
        Type&
        operator[](u64 index);

        /**
         * Subscript operator.
         */
        const Type&
        operator[](u64 index) const;
    };
} // light

#include <light/Base/inline/Buf.inl>

#endif // LIGHT_BASE_BUF_HPP
