#ifndef PAX_BASE_UTIL_HPP
#define PAX_BASE_UTIL_HPP

#include <pax/Base/define.hpp>

/**
 * Prints an error message under a category to standard error and aborts
 * the program.
 */
#define pax_panic(cat, msg, ...) \
    fprintf(stderr, "[%s @ %u] {" cat ": " msg "}\n", \
        __FILE__, __LINE__, __VA_ARGS__), abort()

#define pax_excl(body) \
    body break

#define pax_opt(type, item) \
    static const type item

#endif // PAX_BASE_UTIL_HPP
