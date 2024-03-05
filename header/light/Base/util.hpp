#ifndef LIGHT_BASE_UTIL_HPP
#define LIGHT_BASE_UTIL_HPP

#include <light/Base/define.hpp>

/**
 * Prints an error message under a category to standard error and aborts
 * the program.
 */
#define light_panic(cat, msg, ...) \
    fprintf(stderr, "[%s @ %u] {" cat ": " msg "}\n", \
        __FILE__, __LINE__, __VA_ARGS__), abort()

#endif // LIGHT_BASE_UTIL_HPP
