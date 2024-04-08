#ifndef PAX_ENGINE_INPUTS_HPP
#define PAX_ENGINE_INPUTS_HPP

#include <pax/Engine/define.hpp>

namespace pax
{
    struct Keybd
    {
        static const u64 NUM_0;
        static const u64 NUM_1;
        static const u64 NUM_2;
        static const u64 NUM_3;
        static const u64 NUM_4;
        static const u64 NUM_5;
        static const u64 NUM_6;
        static const u64 NUM_7;
        static const u64 NUM_8;
        static const u64 NUM_9;
        static const u64 A;
        static const u64 B;
        static const u64 C;
        static const u64 D;
        static const u64 E;
        static const u64 F;
        static const u64 G;
        static const u64 H;
        static const u64 I;
        static const u64 J;
        static const u64 K;
        static const u64 L;
        static const u64 M;
        static const u64 N;
        static const u64 O;
        static const u64 P;
        static const u64 Q;
        static const u64 R;
        static const u64 S;
        static const u64 T;
        static const u64 U;
        static const u64 V;
        static const u64 W;
        static const u64 X;
        static const u64 Y;
        static const u64 Z;
        static const u64 UP;
        static const u64 DOWN;
        static const u64 LEFT;
        static const u64 RIGHT;
        static const u64 ESC;
        static const u64 CNTRL_L;
        static const u64 CNTRL_R;
        static const u64 SHIFT_L;
        static const u64 SHIFT_R;
        static const u64 ENTER_L;
        static const u64 ENTER_R;
        static const u64 SYS_L;
        static const u64 SYS_R;
        static const u64 ALT_L;
        static const u64 ALT_R;
    };

    /**
     * todo: Comment.
     */
    bool
    is_keybd_press(u64 key);

    /**
     * todo: Comment.
     */
    bool
    is_keybd_release(u64 key);

    /**
     * todo: Comment.
     */
    u64
    keybd_get_scan(u64 key);

    struct Mouse
    {
        static const u64 LEFT;
        static const u64 CENTRE;
        static const u64 RIGHT;
    };

    /**
     * todo: Comment.
     */
    v2s64
    mouse_coords();

    /**
     * todo: Comment.
     */
    bool
    is_mouse_press(u64 btn);

    /**
     * todo: Comment.
     */
    bool
    is_mouse_release(u64 btn);
} // pax

#endif // PAX_ENGINE_INPUTS_HPP
