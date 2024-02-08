#ifndef LIGHT_BASE_STRING_HPP
#define LIGHT_BASE_STRING_HPP

#include <light/Base/define.hpp>
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
         * Constructor that can be used to provide the
         * desired size of the string, or to trigger a
         * call on "strlen" when called with "MAX_U32".
         */
        String(const s8* data, u32 size = MAX_U32);

        /**
         * Tests if a string contains a specific byte,
         * returns true as soon as it finds an occurrence,
         * or false if none is found.
         */
        bool
        contains(s8 byte) const;

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
    };
} // light

#endif // LIGHT_BASE_STRING_HPP
