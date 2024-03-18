#ifndef PAX_BASE_STRING_HPP
#define PAX_BASE_STRING_HPP

#include <pax/Base/define.hpp>
#include <pax/Base/Opt.hpp>
#include <pax/Base/Buf.hpp>
#include <pax/Base/util.hpp>

namespace pax
{
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
        static String
        build(const s8* data, u64 size);

        /**
         * Constructor that can be used to calculate the size of the string without
         * exceeding a specific upper bound.
         *
         * If the size happens to be larger than the upper bound, this function uses
         * only the first valid portion. Otherwise, if the size is smaller than the
         * lower bound, this function ignores the string completely.
         */
        static String
        build(const s8* data, u64 lower, u64 upper);

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
} // pax

#endif // PAX_BASE_STRING_HPP