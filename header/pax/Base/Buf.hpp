#ifndef PAX_BASE_BUF_HPP
#define PAX_BASE_BUF_HPP

#include <pax/Base/define.hpp>
#include <pax/Base/util.hpp>

namespace pax
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
} // pax

#include <pax/Base/inline/Buf.inl>

#endif // PAX_BASE_BUF_HPP
