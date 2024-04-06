#ifndef PAX_BASE_STRING_HPP
#define PAX_BASE_STRING_HPP

#include <pax/Base/define.hpp>
#include <pax/Base/Store.hpp>

namespace pax
{
    struct String
    {
    public:
        /**
         * Points to an immutable byte array.
         */
        const s8* data = "";

        /**
         * Number of bytes in the array.
         */
        u64 size = 0;

    public:
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
     * Counts the amount of characters contained in a pointer up to a maximum limit, after which returns immediately.
     */
    u64
    string_count(const s8* data, u64 limit);

    /**
     * Creates a string from a pointer and its size, NOT validating the inputs.
     */
    String
    string_create(const s8* data, u64 size);

    /**
     * Creates a string from a pointer and a range of sizes after validating the inputs.
     *
     * If the size of the character sequence is smaller than the lower bound, returns an empty string. Otherwise, if
     * it's larger than the upper bound, immediately returns a string without going beyond the limit.
     */
    String
    string_create(const s8* data, Store<u64, 2u> range);
} // pax

#endif // PAX_BASE_STRING_HPP