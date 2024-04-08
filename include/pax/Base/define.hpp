#ifndef PAX_BASE_DEFINE_HPP
#define PAX_BASE_DEFINE_HPP

/**
 * Determines if the library defines pax_show and pax_show_fmt macros. Those macros print to standard
 * output the source's file and line in which are called, and then a group in which the message is
 * categorized before the message itself.
 *
 * If not defined those macros expand to nothing.
 *
 * Example:
 *   1) pax_show("debug", "Done!");
 *   2) pax_show_fmt("debug", "Result = %u", 3);
 *
 * The difference between the two macros is that pax_show_fmt accepts a format and one or more variables
 * to print, when pax_show only accepts a simple string as message.
 */
#define PAX_DEF_SHOW true

/**
 * Determines if the library defines pax_test and pax_test_fmt macros. Those macros test if a condition
 * is verified: if the condition is verified they do noting; otherwise they print to standard output the
 * source's file and line in which are called, and then a group in which the message is categorized before
 * the message itself (like the pax_show* macros) but also abort the program afterwards.
 *
 * If not defined those macros expand to nothing.
 *
 * Example:
 *   1) pax_test(index < 3, "error", "Index is beyond the limit!");
 *   2) pax_test_fmt(index < 3, "error", "Index = %u is beyond the limit = %lu!", index, 3);
 *
 * The difference between the two macros is that pax_test_fmt accepts a format and one or more variables
 * to print, when pax_test only accepts a simple string as message.
 */
#define PAX_DEF_TEST true

extern "C" {
    #include <stddef.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <math.h>

    // todo: Remove after completion.
    #include <stdio.h>
}

#include <pax/Base/macros.hpp>

namespace pax {
    using u8   = uint8_t;
    using u16  = uint16_t;
    using u32  = uint32_t;
    using u64  = uint64_t;
    using uptr = uintptr_t;

    using s8   = char;
    using s16  = int16_t;
    using s32  = int32_t;
    using s64  = int64_t;
    using sptr = intptr_t;

    using f32 = float;
    using f64 = double;

    /**
     * Static array.
     */
    template <class Item, u64 Size>
    struct Store;

    /**
     * Mathematical vector.
     */
    template <class Item, u64 Size>
    struct Vector;

    template <class Item>
    using Vec2d = Vector<Item, 2u>;

    using v2u64 = Vec2d<u64>;
    using v2s64 = Vec2d<s64>;
    using v2f64 = Vec2d<f64>;

    template <class Item>
    using Vec3d = Vector<Item, 3u>;

    using v3u64 = Vec3d<u64>;
    using v3s64 = Vec3d<s64>;
    using v3f64 = Vec3d<f64>;

    template <class Item>
    using Vec4d = Vector<Item, 4u>;

    using v4u64 = Vec4d<u64>;
    using v4s64 = Vec4d<s64>;
    using v4f64 = Vec4d<f64>;

    /**
     * Optional value.
     */
    template <class Item>
    struct Option;

    /**
     * Immutable string.
     */
    struct String;

    /**
     * Dynamic array.
     */
    template <class Item>
    struct Array;

    /**
     * Dynamic array of two dimensions.
     */
    template <class Item>
    struct Array2d;

    /**
     * List based on a dynamic array.
     */
    template <class Item>
    struct List;

    static const u8   MAX_U8   = UINT8_MAX;
    static const u16  MAX_U16  = UINT16_MAX;
    static const u32  MAX_U32  = UINT32_MAX;
    static const u64  MAX_U64  = UINT64_MAX;
    static const uptr MAX_UPTR = UINTPTR_MAX;

    static const s8   MAX_S8   = INT8_MAX;
    static const s16  MAX_S16  = INT16_MAX;
    static const s32  MAX_S32  = INT32_MAX;
    static const s64  MAX_S64  = INT64_MAX;
    static const sptr MAX_SPTR = INTPTR_MAX;

    static const u8   MIN_U8   = 0;
    static const u16  MIN_U16  = 0;
    static const u32  MIN_U32  = 0;
    static const u64  MIN_U64  = 0;
    static const uptr MIN_UPTR = 0;

    static const s8   MIN_S8   = INT8_MIN;
    static const s16  MIN_S16  = INT16_MIN;
    static const s32  MIN_S32  = INT32_MIN;
    static const s64  MIN_S64  = INT64_MIN;
    static const sptr MIN_SPTR = INTPTR_MIN;

    static const u64 BYTES_U8   = pax_bytes_of(u8);
    static const u64 BYTES_U16  = pax_bytes_of(u16);
    static const u64 BYTES_U32  = pax_bytes_of(u32);
    static const u64 BYTES_U64  = pax_bytes_of(u64);
    static const u64 BYTES_UPTR = pax_bytes_of(uptr);

    static const u64 BYTES_S8   = pax_bytes_of(s8);
    static const u64 BYTES_S16  = pax_bytes_of(s16);
    static const u64 BYTES_S32  = pax_bytes_of(s32);
    static const u64 BYTES_S64  = pax_bytes_of(s64);
    static const u64 BYTES_SPTR = pax_bytes_of(sptr);

    static const u64 BYTES_F32 = pax_bytes_of(f32);
    static const u64 BYTES_F64 = pax_bytes_of(f64);

    static const u64 ALIGN_U8   = pax_align_of(u8);
    static const u64 ALIGN_U16  = pax_align_of(u16);
    static const u64 ALIGN_U32  = pax_align_of(u32);
    static const u64 ALIGN_U64  = pax_align_of(u64);
    static const u64 ALIGN_UPTR = pax_align_of(uptr);

    static const u64 ALIGN_S8   = pax_align_of(s8);
    static const u64 ALIGN_S16  = pax_align_of(s16);
    static const u64 ALIGN_S32  = pax_align_of(s32);
    static const u64 ALIGN_S64  = pax_align_of(s64);
    static const u64 ALIGN_SPTR = pax_align_of(sptr);

    static const u64 ALIGN_F32 = pax_align_of(f32);
    static const u64 ALIGN_F64 = pax_align_of(f64);
} // pax

#endif // PAX_BASE_DEFINE_HPP
