#ifndef PAX_BASE_MACROS_HPP
#define PAX_BASE_MACROS_HPP

#define pax_bytes_of(item) \
    sizeof(item)

#define pax_align_of(item) \
    alignof(item)

#define pax_self \
    (*this)

#define pax_bind \
    pax::invoker_create

#define pax_case_excl(name, ...) \
    case (name): __VA_ARGS__ break

#define pax_case_fall(name) \
    case (name):

#define pax_show_fmt(group, messg, ...)
#define pax_show(group, messg)

#define pax_test_fmt(test, group, messg, ...)
#define pax_test(test, group, messg)

#if PAX_DEF_SHOW
    #undef pax_show_fmt
    #undef pax_show

    #define pax_show_fmt(group, messg, ...)             \
        fprintf(stdout, "[%s, %u] { %s: " messg " }\n", \
            __FILE__, __LINE__, group, __VA_ARGS__      \
        )

    #define pax_show(group, messg)                      \
        fprintf(stdout, "[%s, %u] { %s: " messg " }\n", \
            __FILE__, __LINE__, group                   \
        )
#endif

#if PAX_DEF_TEST
    #undef pax_test_fmt
    #undef pax_test

    #define pax_test_fmt(test, group, messg, ...)           \
        if ( (test) == false ) {                            \
            fprintf(stderr, "[%s, %u] { %s: " messg " }\n", \
                __FILE__, __LINE__, group, __VA_ARGS__      \
            );                                              \
                                                            \
            abort();                                        \
        }

    #define pax_test(test, group, messg)                    \
        if ( (test) == false ) {                            \
            fprintf(stderr, "[%s, %u] { %s: " messg " }\n", \
                __FILE__, __LINE__, group                   \
            );                                              \
                                                            \
            abort();                                        \
        }
#endif

#endif // PAX_BASE_MACROS_HPP
