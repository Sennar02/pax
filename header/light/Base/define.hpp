#ifndef LIGHT_BASE_DEFINE_HPP
#define LIGHT_BASE_DEFINE_HPP

extern "C" {
    #include <stdint.h>
    #include <stddef.h>
    #include <string.h>
    #include <math.h>

    // TODO: To remove after debugging.
    #include <stdio.h>
}

namespace light {
    // Some unsigned integer types.
    using u8   = uint8_t;
    using u16  = uint16_t;
    using u32  = uint32_t;
    using u64  = uint64_t;
    using uptr = uintptr_t;

    // Some signed integer types.
    using s8   = char;
    using s16  = int16_t;
    using s32  = int32_t;
    using s64  = int64_t;
    using sptr = intptr_t;

    // Some floating point types.
    using f32 = float;
    using f64 = double;

    /**
     * Mathematical vector of arbitrary
     * type and size.
     */
    template <class Type, u64 Size>
    struct Vec;

    using v2u64 = Vec<u64, 2u>;
    using v2s64 = Vec<s64, 2u>;
    using v2f64 = Vec<f64, 2u>;

    using v3u64 = Vec<u64, 3u>;
    using v3s64 = Vec<s64, 3u>;
    using v3f64 = Vec<f64, 3u>;

    using v4u64 = Vec<u64, 4u>;
    using v4s64 = Vec<s64, 4u>;
    using v4f64 = Vec<f64, 4u>;

    /**
     * Simple static array of arbitrary
     * type and size.
     */
    template <class Type, u64 Size>
    struct Buf;

    /**
     * Tagged union type to communicate
     * if an operation succeds or fails.
     */
    template <class Type, class Fail>
    struct Res;

    /**
     * Optional value.
     */
    template <class Type>
    struct Opt;

    /**
     * String view.
     */
    struct String;

    // Maximum values for unsigned integer types.
    static const u8   MAX_U8   = UINT8_MAX;
    static const u16  MAX_U16  = UINT16_MAX;
    static const u32  MAX_U32  = UINT32_MAX;
    static const u64  MAX_U64  = UINT64_MAX;
    static const uptr MAX_UPTR = UINTPTR_MAX;

    // Maximum values for signed integer types.
    static const s8   MAX_S8   = INT8_MAX;
    static const s16  MAX_S16  = INT16_MAX;
    static const s32  MAX_S32  = INT32_MAX;
    static const s64  MAX_S64  = INT64_MAX;
    static const sptr MAX_SPTR = INTPTR_MAX;

    // Minimum values for unsigned integer types.
    static const u8   MIN_U8   = 0;
    static const u16  MIN_U16  = 0;
    static const u32  MIN_U32  = 0;
    static const u64  MIN_U64  = 0;
    static const uptr MIN_UPTR = 0;

    // Minimum values for signed integer types.
    static const s8   MIN_S8   = INT8_MIN;
    static const s16  MIN_S16  = INT16_MIN;
    static const s32  MIN_S32  = INT32_MIN;
    static const s64  MIN_S64  = INT64_MIN;
    static const sptr MIN_SPTR = INTPTR_MIN;

    // Size in bytes for unsigned integer types.
    static const u8 LEN_U8   = sizeof(u8);
    static const u8 LEN_U16  = sizeof(u16);
    static const u8 LEN_U32  = sizeof(u32);
    static const u8 LEN_U64  = sizeof(u64);
    static const u8 LEN_UPTR = sizeof(uptr);

    // Size in bytes for signed integer types.
    static const u8 LEN_S8   = sizeof(s8);
    static const u8 LEN_S16  = sizeof(s16);
    static const u8 LEN_S32  = sizeof(s32);
    static const u8 LEN_S64  = sizeof(s64);
    static const u8 LEN_SPTR = sizeof(sptr);

    // Size in bytes for floating point types.
    static const u8 LEN_F32 = sizeof(f32);
    static const u8 LEN_F64 = sizeof(f64);
} // light

#define LIGHT_TEST_BOUNDS true

#define light_panic(cat, msg, ...) \
    fprintf(stderr, "[%s@%u] {" cat ": " msg "}\n", __FILE__, __LINE__, __VA_ARGS__), exit(1);

#endif // LIGHT_BASE_DEFINE_HPP
