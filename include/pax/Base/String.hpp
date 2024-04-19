#ifndef PAX_BASE_STRING_HPP
#define PAX_BASE_STRING_HPP

#include <pax/Base/define.hpp>
#include <pax/Base/Storage.hpp>

namespace pax
{
    struct String
    {
    public:
        /**
         * Points to an array of immutable bytes.
         */
        const s8* data = "";

        /**
         * Number of bytes in the array.
         */
        u64 size = 0;

    public:
        /**
         * Default constructor to make the compiler happy.
         */
        String();

        /**
         * Returns the element contained in a particular index.
         */
        s8
        item(u64 index) const;

        /**
         * Returns the element contained in a particular index.
         */
        s8
        operator()(u64 index) const;
    };

    /**
     * Counts the amount of characters contained in an array up to a maximum limit, after which returns immediately.
     */
    u64
    string_count(const s8* data, u64 limit);

    /**
     * Creates a string from an array and its size, NOT VALIDATING the inputs.
     */
    String
    string_create(const s8* data, u64 size);

    /**
     * Creates a string from an array and a range of sizes after validating the inputs.
     *
     * If the size of the character sequence is smaller than the lower bound, returns an empty string. Otherwise, if
     * it's larger than the upper bound, immediately returns a string without going beyond the limit.
     */
    String
    string_create(const s8* data, Storage<u64, 2u> range);
} // pax

#endif // PAX_BASE_STRING_HPP
