#include <pax/Engine/Signal/Keybd_Signal.hpp>

namespace pax
{
    const u64 Keybd_Symb::NUM_0   = SDLK_0;
    const u64 Keybd_Symb::NUM_1   = SDLK_1;
    const u64 Keybd_Symb::NUM_2   = SDLK_2;
    const u64 Keybd_Symb::NUM_3   = SDLK_3;
    const u64 Keybd_Symb::NUM_4   = SDLK_4;
    const u64 Keybd_Symb::NUM_5   = SDLK_5;
    const u64 Keybd_Symb::NUM_6   = SDLK_6;
    const u64 Keybd_Symb::NUM_7   = SDLK_7;
    const u64 Keybd_Symb::NUM_8   = SDLK_8;
    const u64 Keybd_Symb::NUM_9   = SDLK_9;
    const u64 Keybd_Symb::A       = SDLK_a;
    const u64 Keybd_Symb::B       = SDLK_b;
    const u64 Keybd_Symb::C       = SDLK_c;
    const u64 Keybd_Symb::D       = SDLK_d;
    const u64 Keybd_Symb::E       = SDLK_e;
    const u64 Keybd_Symb::F       = SDLK_f;
    const u64 Keybd_Symb::G       = SDLK_g;
    const u64 Keybd_Symb::H       = SDLK_h;
    const u64 Keybd_Symb::I       = SDLK_i;
    const u64 Keybd_Symb::J       = SDLK_j;
    const u64 Keybd_Symb::K       = SDLK_k;
    const u64 Keybd_Symb::L       = SDLK_l;
    const u64 Keybd_Symb::M       = SDLK_m;
    const u64 Keybd_Symb::N       = SDLK_n;
    const u64 Keybd_Symb::O       = SDLK_o;
    const u64 Keybd_Symb::P       = SDLK_p;
    const u64 Keybd_Symb::Q       = SDLK_q;
    const u64 Keybd_Symb::R       = SDLK_r;
    const u64 Keybd_Symb::S       = SDLK_s;
    const u64 Keybd_Symb::T       = SDLK_t;
    const u64 Keybd_Symb::U       = SDLK_u;
    const u64 Keybd_Symb::V       = SDLK_v;
    const u64 Keybd_Symb::W       = SDLK_w;
    const u64 Keybd_Symb::X       = SDLK_x;
    const u64 Keybd_Symb::Y       = SDLK_y;
    const u64 Keybd_Symb::Z       = SDLK_z;
    const u64 Keybd_Symb::UP      = SDLK_UP;
    const u64 Keybd_Symb::DOWN    = SDLK_DOWN;
    const u64 Keybd_Symb::LEFT    = SDLK_LEFT;
    const u64 Keybd_Symb::RIGHT   = SDLK_RIGHT;
    const u64 Keybd_Symb::ESC     = SDLK_ESCAPE;
    const u64 Keybd_Symb::CNTRL_L = SDLK_LCTRL;
    const u64 Keybd_Symb::CNTRL_R = SDLK_RCTRL;
    const u64 Keybd_Symb::SHIFT_L = SDLK_LSHIFT;
    const u64 Keybd_Symb::SHIFT_R = SDLK_RSHIFT;
    const u64 Keybd_Symb::ENTER_L = SDLK_RETURN;
    const u64 Keybd_Symb::ENTER_R = SDLK_RETURN2;
    const u64 Keybd_Symb::SYS_L   = SDLK_LGUI;
    const u64 Keybd_Symb::SYS_R   = SDLK_RGUI;
    const u64 Keybd_Symb::ALT_L   = SDLK_LALT;
    const u64 Keybd_Symb::ALT_R   = SDLK_RALT;

    const u64 Keybd_Phys::NUM_0   = SDL_SCANCODE_0;
    const u64 Keybd_Phys::NUM_1   = SDL_SCANCODE_1;
    const u64 Keybd_Phys::NUM_2   = SDL_SCANCODE_2;
    const u64 Keybd_Phys::NUM_3   = SDL_SCANCODE_3;
    const u64 Keybd_Phys::NUM_4   = SDL_SCANCODE_4;
    const u64 Keybd_Phys::NUM_5   = SDL_SCANCODE_5;
    const u64 Keybd_Phys::NUM_6   = SDL_SCANCODE_6;
    const u64 Keybd_Phys::NUM_7   = SDL_SCANCODE_7;
    const u64 Keybd_Phys::NUM_8   = SDL_SCANCODE_8;
    const u64 Keybd_Phys::NUM_9   = SDL_SCANCODE_9;
    const u64 Keybd_Phys::A       = SDL_SCANCODE_A;
    const u64 Keybd_Phys::B       = SDL_SCANCODE_B;
    const u64 Keybd_Phys::C       = SDL_SCANCODE_C;
    const u64 Keybd_Phys::D       = SDL_SCANCODE_D;
    const u64 Keybd_Phys::E       = SDL_SCANCODE_E;
    const u64 Keybd_Phys::F       = SDL_SCANCODE_F;
    const u64 Keybd_Phys::G       = SDL_SCANCODE_G;
    const u64 Keybd_Phys::H       = SDL_SCANCODE_H;
    const u64 Keybd_Phys::I       = SDL_SCANCODE_I;
    const u64 Keybd_Phys::J       = SDL_SCANCODE_J;
    const u64 Keybd_Phys::K       = SDL_SCANCODE_K;
    const u64 Keybd_Phys::L       = SDL_SCANCODE_L;
    const u64 Keybd_Phys::M       = SDL_SCANCODE_M;
    const u64 Keybd_Phys::N       = SDL_SCANCODE_N;
    const u64 Keybd_Phys::O       = SDL_SCANCODE_O;
    const u64 Keybd_Phys::P       = SDL_SCANCODE_P;
    const u64 Keybd_Phys::Q       = SDL_SCANCODE_Q;
    const u64 Keybd_Phys::R       = SDL_SCANCODE_R;
    const u64 Keybd_Phys::S       = SDL_SCANCODE_S;
    const u64 Keybd_Phys::T       = SDL_SCANCODE_T;
    const u64 Keybd_Phys::U       = SDL_SCANCODE_U;
    const u64 Keybd_Phys::V       = SDL_SCANCODE_V;
    const u64 Keybd_Phys::W       = SDL_SCANCODE_W;
    const u64 Keybd_Phys::X       = SDL_SCANCODE_X;
    const u64 Keybd_Phys::Y       = SDL_SCANCODE_Y;
    const u64 Keybd_Phys::Z       = SDL_SCANCODE_Z;
    const u64 Keybd_Phys::UP      = SDL_SCANCODE_UP;
    const u64 Keybd_Phys::DOWN    = SDL_SCANCODE_DOWN;
    const u64 Keybd_Phys::LEFT    = SDL_SCANCODE_LEFT;
    const u64 Keybd_Phys::RIGHT   = SDL_SCANCODE_RIGHT;
    const u64 Keybd_Phys::ESC     = SDL_SCANCODE_ESCAPE;
    const u64 Keybd_Phys::CNTRL_L = SDL_SCANCODE_LCTRL;
    const u64 Keybd_Phys::CNTRL_R = SDL_SCANCODE_RCTRL;
    const u64 Keybd_Phys::SHIFT_L = SDL_SCANCODE_LSHIFT;
    const u64 Keybd_Phys::SHIFT_R = SDL_SCANCODE_RSHIFT;
    const u64 Keybd_Phys::ENTER_L = SDL_SCANCODE_RETURN;
    const u64 Keybd_Phys::ENTER_R = SDL_SCANCODE_RETURN2;
    const u64 Keybd_Phys::SYS_L   = SDL_SCANCODE_LGUI;
    const u64 Keybd_Phys::SYS_R   = SDL_SCANCODE_RGUI;
    const u64 Keybd_Phys::ALT_L   = SDL_SCANCODE_LALT;
    const u64 Keybd_Phys::ALT_R   = SDL_SCANCODE_RALT;

    const u64 Keybd_Signal::KIND = Signal_Kind::KEYBD;

    u64
    Keybd_Signal::kind() const
    {
        return Keybd_Signal::KIND;
    }

    bool
    Keybd_Signal::is_repeat() const
    {
        return bits_test(flags, FLAG_REPEAT);
    }

    bool
    Keybd_Signal::is_press() const
    {
        return bits_test(flags, FLAG_PRESS);
    }

    bool
    Keybd_Signal::is_release() const
    {
        return bits_test(flags, FLAG_PRESS) == false;
    }
} // pax
