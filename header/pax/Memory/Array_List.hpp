#ifndef PAX_MEMORY_ARRAY_LIST_HPP
#define PAX_MEMORY_ARRAY_LIST_HPP

#include <pax/Memory/define.hpp>
#include <pax/Memory/Array.hpp>

namespace pax
{
    template <class Type>
    struct Array_List
    {
    public:
        /**
         *
         */
        Array<Type> array;

        /**
         *
         */
        u64 count = 0;

    public:
        /**
         *
         */
        static Array_List<Type>
        build(void* data, u64 size);

        /**
         *
         */
        static Array_List<Type>
        build(u64 size, Alloc* alloc);

        /**
         *
         */
        bool
        create(u64 size, Alloc* alloc);

        /**
         *
         */
        bool
        create(u64 size);

        /**
         *
         */
        bool
        destroy();

        /**
         *
         */
        bool
        swap(u64 index, u64 other);

        /**
         *
         */
        bool
        move(u64 index, s64 displ);

        /**
         *
         */
        bool
        insert(Type item, u64 index);

        /**
         *
         */
        Opt<Type>
        remove(u64 index);
    };
} // pax

#include <pax/Memory/inline/Array_List.inl>

#endif // PAX_MEMORY_ARRAY_LIST_HPP