#ifndef PAX_MEMORY_BUILDER_HPP
#define PAX_MEMORY_BUILDER_HPP

#include <pax/Memory/define.hpp>
#include <pax/Memory/Alloc.hpp>

namespace pax
{
    struct Builder
    {
    public:
        /**
         *
         */
        Alloc* alloc = 0;

    public:
        /**
         *
         */
        template <class Type, class... Args>
        Type*
        reserve(Args... args);

        /**
         *
         */
        template <class Type>
        bool
        reclaim(Type* addr);

        /**
         *
         */
        Builder&
        reset();
    };
} // pax

#include <pax/Memory/inline/Builder.inl>

#endif // PAX_MEMORY_BUILDER_HPP
