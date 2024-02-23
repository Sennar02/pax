#ifndef LIGHT_BASE_STRING_HPP
#define LIGHT_BASE_STRING_HPP

#include <light/Base/define.hpp>
#include <light/Base/Opt.hpp>
#include <light/Base/Buffer.hpp>

namespace light
{
    using Byte_Table = Buffer<u8, 256u>;

    struct String
    {
    public:
        /**
         * Commonly trimmed characters.
         */
        static const Byte_Table TRIMS;

        /**
         * Table of digits to parse a binary number.
         */
        static const Byte_Table BASE_2;

        /**
         * Table of digits to parse an octal number.
         */
        static const Byte_Table BASE_8;

        /**
         * Table of digits to parse a decimal number.
         */
        static const Byte_Table BASE_10;

        /**
         * Table of digits to parse an hexadecimal number.
         */
        static const Byte_Table BASE_16;

    public:
        /**
         * Pointer to the characters.
         */
        const s8* data;

        /**
         * Amount of characters.
         */
        u64 size;

    public:
        /**
         * Default constructor.
         */
        String();

        /**
         * Constructor that can be used to provide
         * the desired size of the string.
         *
         * WARNING: There is no way that the constructor
         *          can detect if the size exceeds the
         *          size of the allocation for the pointer.
         */
        String(const s8* data, u64 size);

        /**
         * Constructor that can be used to calculate
         * the size of the string. If the size is smaller
         * than the lower bound the string is ignored
         * altogether, if instead the size is bigger than
         * the upper bound: it just stops counting.
         */
        String(const s8* data, u64 lower, u64 upper);

        /**
         * Tests if a string contains a specific byte,
         * returns true as soon as it finds an occurrence,
         * or false if none is found.
         */
        bool
        contains(s8 byte) const;

        /**
         * Tests if a string contains a specific byte,
         * returns the index of the first occurrence,
         * of an empty value if none is found.
         */
        Opt<u64>
        index_of(s8 byte) const;

        /**
         * Creates two substrings. The first one ranges from
         * the start of the original string to the first
         * occurrence of a specific byte, the second
         * one ranges from after the first occurrence of
         * the same byte to the end of the original string.
         */
        Buffer<String, 2u>
        split(char byte) const;

        /**
         * Excludes from the string any byte specified in
         * the argument, exclusively on the left side, until
         * it finds any unspecified byte.
         */
        String&
        trim_left(const Byte_Table& table = TRIMS);

        /**
         * Excludes from the string any byte specified in
         * the argument, exclusively on the right side, until
         * it finds any unspecified byte.
         */
        String&
        trim_right(const Byte_Table& table = TRIMS);

        /**
         * Excludes from the string any byte specified in
         * the argument, on both sides, until it finds any
         * unspecified byte.
         */
        String&
        trim(const Byte_Table& table = TRIMS);

        /**
         * Subscript operator, doesn't test bounds.
         */
        char
        operator[](u64 index) const;
    };

    s64
    parse_int(
        String            string,
        const Byte_Table& table = String::BASE_10,
        u8                radix = 10u
    );

    f64
    parse_flt(
        String            string,
        const Byte_Table& table = String::BASE_10,
        u8                radix = 10u
    );
} // light

#endif // LIGHT_BASE_STRING_HPP
