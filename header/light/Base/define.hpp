#ifndef LIGHT_BASE_DEFINE_HPP
#define LIGHT_BASE_DEFINE_HPP

extern "C" {
    #include <stdint.h>
    #include <stddef.h>
    #include <math.h>

    // TODO: To remove after debugging.
    #include <stdio.h>
}

namespace light {
    // Some unsigned integer type.
    using u8   = uint8_t;
    using u16  = uint16_t;
    using u32  = uint32_t;
    using u64  = uint64_t;
    using uptr = uintptr_t;

    // Some signed integer type.
    using s8   = char;
    using s16  = int16_t;
    using s32  = int32_t;
    using s64  = int64_t;
    using sptr = intptr_t;

    // Some floating point type.
    using f32 = float;
    using f64 = double;

    /**
     * Mathematical vector of arbitrary
     * type and size.
     */
    template <class Type, u32 Size>
    struct Vec;

    using Vec2u = Vec<u32, 2u>;
    using Vec2s = Vec<s32, 2u>;
    using Vec2f = Vec<f32, 2u>;

    using Vec3u = Vec<u32, 3u>;
    using Vec3s = Vec<s32, 3u>;
    using Vec3f = Vec<f32, 3u>;

    using Vec4u = Vec<u32, 4u>;
    using Vec4s = Vec<s32, 4u>;
    using Vec4f = Vec<f32, 4u>;

    /**
     * Simple static array of arbitrary
     * type and size.
     */
    template <class Type, u32 Size>
    struct Buffer;

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

    // Maximum values for each unsigned integer type.
    static const u8   MAX_U8   = UINT8_MAX;
    static const u16  MAX_U16  = UINT16_MAX;
    static const u32  MAX_U32  = UINT32_MAX;
    static const u64  MAX_U64  = UINT64_MAX;
    static const uptr MAX_UPTR = UINTPTR_MAX;

    // Maximum values for each signed integer type.
    static const s8   MAX_S8   = INT8_MAX;
    static const s16  MAX_S16  = INT16_MAX;
    static const s32  MAX_S32  = INT32_MAX;
    static const s64  MAX_S64  = INT64_MAX;
    static const sptr MAX_SPTR = INTPTR_MAX;

    // Minimum values for each unsigned integer type.
    static const u8   MIN_U8   = 0;
    static const u16  MIN_U16  = 0;
    static const u32  MIN_U32  = 0;
    static const u64  MIN_U64  = 0;
    static const uptr MIN_UPTR = 0;

    // Minimum values for each signed integer type.
    static const s8   MIN_S8   = INT8_MIN;
    static const s16  MIN_S16  = INT16_MIN;
    static const s32  MIN_S32  = INT32_MIN;
    static const s64  MIN_S64  = INT64_MIN;
    static const sptr MIN_SPTR = INTPTR_MIN;

    // Size in bytes for each unsigned integer type.
    static const u8 LEN_U8   = sizeof(u8);
    static const u8 LEN_U16  = sizeof(u16);
    static const u8 LEN_U32  = sizeof(u32);
    static const u8 LEN_U64  = sizeof(u64);
    static const u8 LEN_UPTR = sizeof(uptr);

    // Size in bytes for each signed integer type.
    static const u8 LEN_S8   = LEN_U8;
    static const u8 LEN_S16  = LEN_U16;
    static const u8 LEN_S32  = LEN_U32;
    static const u8 LEN_S64  = LEN_U64;
    static const u8 LEN_SPTR = LEN_UPTR;

    // Size in bytes for each floating point type.
    static const u8 LEN_F32 = LEN_U32;
    static const u8 LEN_F64 = LEN_F64;
} // light

/**
 * Compares two values and chooses the bigger one.
 */
#define light_max(a, b) \
    (a < b ? b : a)

/**
 * Compares two values and chooses the smaller one.
 */
#define light_min(a, b) \
    (a < b ? a : b)

/**
 * Determines if a value is inside a range. The
 * range is assumed to be in the form [a, b].
 *
 * Note: The case a > b is tested.
 */
#define light_is_in(a, b, v) \
    (a <= b && a <= v && v <= b)

/**
 * Confines a value within a range. The range
 * is assumed to be in the form [a, b].
 */
#define light_clamp(a, b, v) \
    light_min(b, light_max(a, v))

#endif // LIGHT_BASE_DEFINE_HPP
