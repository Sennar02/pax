#ifndef LIGHT_BASE_STRING_HPP
#define LIGHT_BASE_STRING_HPP

#include <light/Base/define.hpp>
#include <light/Base/Opt.hpp>
#include <light/Base/Array.hpp>

namespace light
{
    struct String
    {
    public:
        /**
         * Commonly trimmed characters, used as a
         * default argument for any trim function.
         */
        static const String TRIMS;

        /**
         * Table of digits for a base 10 number.
         */
        static const String BASE_10;

        /**
         * Table of digits for a base 16 number.
         */
        static const String BASE_16;

    public:
        /**
         * Pointer to the characters.
         */
        const s8* data;

        /**
         * Amount of characters.
         */
        u32 size;

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
        String(const s8* data, u32 size);

        /**
         * Constructor that can be used to calculate
         * the size of the string. If the size is smaller
         * than the lower bound the string is ignored
         * altogether, if instead the size is bigger than
         * the upper bound: it just stops counting.
         */
        String(const s8* data, u32 lower, u32 upper);

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
        Opt<u32>
        index_of(s8 byte) const;

        /**
         * Creates two substrings. The first one ranges from
         * the start of the original string to the first
         * occurrence of a specific byte, the second
         * one ranges from after the first occurrence of
         * the same byte to the end of the original string.
         */
        Array<String, 2u>
        split(char byte) const;

        /**
         * Excludes from the string any byte specified in
         * the argument, exclusively on the left side, until
         * it finds any unspecified byte.
         */
        String&
        trim_left(String bytes = TRIMS);

        /**
         * Excludes from the string any byte specified in
         * the argument, exclusively on the right side, until
         * it finds any unspecified byte.
         */
        String&
        trim_right(String bytes = TRIMS);

        /**
         * Excludes from the string any byte specified in
         * the argument, on both sides, until it finds any
         * unspecified byte.
         */
        String&
        trim(String bytes = TRIMS);

        /**
         * Subscript operator, doesn't test bounds.
         */
        char
        operator[](u32 index) const;
    };

    s32
    parse_int(String string, String digits = String::BASE_10);

    f32
    parse_flt(String string, String digits = String::BASE_10);
} // light

#endif // LIGHT_BASE_STRING_HPP
