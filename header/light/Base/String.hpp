#ifndef LIGHT_BASE_STRING_HPP
#define LIGHT_BASE_STRING_HPP

#include <light/Base/define.hpp>
#include <light/Base/Opt.hpp>
#include <light/Base/Buf.hpp>
#include <light/Base/util.hpp>

namespace light
{
    using Byte_Table = Buf<u8, 256u>;

    /**
     * Bytes commonly excluded from strings.
     */
    extern const Byte_Table STRING_TRIM;

    struct String
    {
    public:
        /**
         * Pointer to immutable bytes.
         */
        const s8* data = "";

        /**
         * Number of bytes.
         */
        u64 size = 0;

    public:
        /**
         * Default constructor to make the compiler happy.
         */
        String();

        /**
         * Constructor that can be used to provide a specific size for the string.
         *
         * !!! WARNING !!!
         *
         * This function cannot test if the size is valid or not, because of this,
         * providing one larger than the allocated space can lead to:
         *  - memory corruptions,
         *  - crashes,
         *  - vulnerabilities.
         */
        String(const s8* data, u64 size);

        /**
         * Constructor that can be used to calculate the size of the string without
         * exceeding a specific upper bound.
         *
         * If the size happens to be larger than the upper bound, this function uses
         * only the first valid portion. Otherwise, if the size is smaller than the
         * lower bound, this function ignores the string completely.
         */
        String(const s8* data, u64 lower, u64 upper);

        /**
         * Tests if a string contains a specific byte. Returns true as soon as it
         * finds an occurrence, or false if none is found.
         */
        bool
        contains(s8 byte) const;

        /**
         * Tests if a string contains a specific byte. Returns the index of the first
         * occurrence as soon as it finds one, or an empty optional if none is found.
         */
        Opt<u64>
        index_of(s8 byte) const;

        /**
         * Divides the string in two parts. The first one ranges from the start of the
         * original string until the first occurrence of the specified byte, while the
         * second one ranges from after the same occurrence to the end of the original
         * string.
         *
         * For example:
         *  1) String("Byte byte!", 10u).split(' ')
         *      will produce ["Byte", "byte!"]
         *
         *  2) String("Byte byte!", 10u).split('!')
         *      will produce ["Byte byte", ""]
         *
         *  3) String("Byte byte!", 10u).split('B')
         *      will produce ["", "yte byte!"]
         */
        Buf<String, 2u>
        split(char byte) const;

        /**
         * Excludes from the head of the string any byte specified in the table.
         */
        String&
        trim_left(const Byte_Table& table = STRING_TRIM);

        /**
         * Excludes from the tail of the string any byte specified in the table.
         */
        String&
        trim_right(const Byte_Table& table = STRING_TRIM);

        /**
         * Excludes from both ends of the string any byte specified in the table.
         */
        String&
        trim(const Byte_Table& table = STRING_TRIM);

        /**
         * Subscript operator.
         */
        const s8&
        operator[](u64 index) const;
    };

    /**
     * Tries to read an unsigned integer from a string.
     *
     * The number has to be in the following form:
     *  - Any digit from 0 to 9.
     */
    u64
    parse_u64(String string);

    /**
     * Tries to read a signed integer from a string.
     *
     * The number has to be in the following form:
     *  - Optional "+" or "-",
     *  - Any digit from 0 to 9.
     *
     * It tries to match as much as possible before
     * returning.
     *
     * For example:
     *  1) -145  will produce -145,
     *  2) 12-12 will produce 12, (Ignores the -12)
     *  3) +-3   will produce 0. (Ignores the -3)
     */
    s64
    parse_s64(String string);

    /**
     * Tries to read a floating point from a string.
     *
     * The number has to be in the following form:
     *  - Optional "+" or "-",
     *  - Any digit from 0 to 9,
     *  - Optional ".",
     *  - Optionals digits from 0 to 9,
     *  - Optional "e" or "E",
     *  - Optional "+" or "-",
     *  - Optionals digits from 0 to 9.
     *
     * It tries to match as much as possible before
     * returning.
     *
     * For example:
     *  1) -1e-2     will produce -0.01
     *  2) -.e+3     will produce 0
     *  3) 12.3e-1.3 will produce 1.23 (Ignores the .3)
     *  4) .4        will produce 0.4
     *  5) 4.        will produce 4
     *  6) 3.e       will produce 3
     */
    f64
    parse_f64(String string);
} // light

#endif // LIGHT_BASE_STRING_HPP
