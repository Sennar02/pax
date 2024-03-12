#ifndef PAX_ENGINE_KEYBD_EVENT_HPP
#define PAX_ENGINE_KEYBD_EVENT_HPP

#include <pax/Engine/define.hpp>
#include <pax/Signal/Signal.hpp>

namespace pax
{
    struct Keybd_Signal
        : public Signal
    {
    public:
        enum Flag
        {
            FLAG_REPEAT = 0x01,
            FLAG_PRESS  = 0x02,
        };

        /**
         *
         */
        static const u64 KIND;

    public:
        /**
         *
         */
        u64 physic = 0;

        /**
         *
         */
        u64 symbol = 0;

        /**
         *
         */
        u64 modifs = 0;

        /**
         *
         */
        u64 flags  = 0;

    public:
        /**
         *
         */
        u64
        kind() const;

        /**
         *
         */
        bool
        is_repeat() const;

        /**
         *
         */
        bool
        is_press() const;

        /**
         *
         */
        bool
        is_release() const;
    };

    struct Keybd_Symb
    {
        pax_opt(u64, NUM_0);
        pax_opt(u64, NUM_1);
        pax_opt(u64, NUM_2);
        pax_opt(u64, NUM_3);
        pax_opt(u64, NUM_4);
        pax_opt(u64, NUM_5);
        pax_opt(u64, NUM_6);
        pax_opt(u64, NUM_7);
        pax_opt(u64, NUM_8);
        pax_opt(u64, NUM_9);
        pax_opt(u64, A);
        pax_opt(u64, B);
        pax_opt(u64, C);
        pax_opt(u64, D);
        pax_opt(u64, E);
        pax_opt(u64, F);
        pax_opt(u64, G);
        pax_opt(u64, H);
        pax_opt(u64, I);
        pax_opt(u64, J);
        pax_opt(u64, K);
        pax_opt(u64, L);
        pax_opt(u64, M);
        pax_opt(u64, N);
        pax_opt(u64, O);
        pax_opt(u64, P);
        pax_opt(u64, Q);
        pax_opt(u64, R);
        pax_opt(u64, S);
        pax_opt(u64, T);
        pax_opt(u64, U);
        pax_opt(u64, V);
        pax_opt(u64, W);
        pax_opt(u64, X);
        pax_opt(u64, Y);
        pax_opt(u64, Z);
        pax_opt(u64, UP);
        pax_opt(u64, DOWN);
        pax_opt(u64, LEFT);
        pax_opt(u64, RIGHT);
        pax_opt(u64, ESC);
        pax_opt(u64, CNTRL_L);
        pax_opt(u64, CNTRL_R);
        pax_opt(u64, SHIFT_L);
        pax_opt(u64, SHIFT_R);
        pax_opt(u64, ENTER_L);
        pax_opt(u64, ENTER_R);
        pax_opt(u64, SYS_L);
        pax_opt(u64, SYS_R);
        pax_opt(u64, ALT_L);
        pax_opt(u64, ALT_R);
    };

    struct Keybd_Phys
    {
        pax_opt(u64, NUM_0);
        pax_opt(u64, NUM_1);
        pax_opt(u64, NUM_2);
        pax_opt(u64, NUM_3);
        pax_opt(u64, NUM_4);
        pax_opt(u64, NUM_5);
        pax_opt(u64, NUM_6);
        pax_opt(u64, NUM_7);
        pax_opt(u64, NUM_8);
        pax_opt(u64, NUM_9);
        pax_opt(u64, A);
        pax_opt(u64, B);
        pax_opt(u64, C);
        pax_opt(u64, D);
        pax_opt(u64, E);
        pax_opt(u64, F);
        pax_opt(u64, G);
        pax_opt(u64, H);
        pax_opt(u64, I);
        pax_opt(u64, J);
        pax_opt(u64, K);
        pax_opt(u64, L);
        pax_opt(u64, M);
        pax_opt(u64, N);
        pax_opt(u64, O);
        pax_opt(u64, P);
        pax_opt(u64, Q);
        pax_opt(u64, R);
        pax_opt(u64, S);
        pax_opt(u64, T);
        pax_opt(u64, U);
        pax_opt(u64, V);
        pax_opt(u64, W);
        pax_opt(u64, X);
        pax_opt(u64, Y);
        pax_opt(u64, Z);
        pax_opt(u64, UP);
        pax_opt(u64, DOWN);
        pax_opt(u64, LEFT);
        pax_opt(u64, RIGHT);
        pax_opt(u64, ESC);
        pax_opt(u64, CNTRL_L);
        pax_opt(u64, CNTRL_R);
        pax_opt(u64, SHIFT_L);
        pax_opt(u64, SHIFT_R);
        pax_opt(u64, ENTER_L);
        pax_opt(u64, ENTER_R);
        pax_opt(u64, SYS_L);
        pax_opt(u64, SYS_R);
        pax_opt(u64, ALT_L);
        pax_opt(u64, ALT_R);
    };
} // pax

#endif // PAX_ENGINE_KEYBD_EVENT_HPP
