#ifndef PAX_BASE_MACROS_HPP
#define PAX_BASE_MACROS_HPP

#define pax_bytes_of(item) \
    sizeof(item)

#define pax_align_of(item) \
    alignof(item)

#define pax_self \
    (*this)

#define pax_case_excl(name, ...) \
    case (name): __VA_ARGS__ break

#define pax_case_fall(name, ...) \
    case (name): __VA_ARGS__

#define pax_show_fmt(group, error, ...)
#define pax_show(group, error)

#define pax_test_fmt(test, group, error, ...)
#define pax_test(test, group, error)

#if PAX_DEF_SHOW
    #undef pax_show_fmt
    #undef pax_show

    #define pax_show_fmt(group, error, ...)                   \
        fprintf(stderr, "[%s, %u] {" group ": " error "}\n",  \
            __FILE__, __LINE__, __VA_ARGS__                   \
        )

    #define pax_show(group, error)                            \
        fprintf(stderr, "[%s, %u] {" group ": " error "}\n",  \
            __FILE__, __LINE__                                \
        )
#endif

#if PAX_DEF_TEST
    #undef pax_test_fmt
    #undef pax_test

    #define pax_test_fmt(test, group, error, ...)                 \
        if ( (test) == false ) {                                  \
            pax_show_fmt(group, error, __VA_ARGS__); abort();     \
        }

    #define pax_test(test, group, error)                          \
        if ( (test) == false ) {                                  \
            pax_show(group, error); abort();                      \
        }
#endif

#endif // PAX_BASE_MACROS_HPP
