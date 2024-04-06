#include <pax/Engine/Inputs.hpp>

// SDL_GetKeyboardState, SDL_GetScancodeFromKey,
// SDL_GetMouseState, SDL_PumpEvents.
#include <SDL2/SDL_events.h>

namespace pax
{
    static u64 keybd_size = 0;
    static u8* keybd_data =
        (u8*) SDL_GetKeyboardState((s32*) &keybd_size);

    const u64 Keybd::NUM_0   = SDLK_0;
    const u64 Keybd::NUM_1   = SDLK_1;
    const u64 Keybd::NUM_2   = SDLK_2;
    const u64 Keybd::NUM_3   = SDLK_3;
    const u64 Keybd::NUM_4   = SDLK_4;
    const u64 Keybd::NUM_5   = SDLK_5;
    const u64 Keybd::NUM_6   = SDLK_6;
    const u64 Keybd::NUM_7   = SDLK_7;
    const u64 Keybd::NUM_8   = SDLK_8;
    const u64 Keybd::NUM_9   = SDLK_9;
    const u64 Keybd::A       = SDLK_a;
    const u64 Keybd::B       = SDLK_b;
    const u64 Keybd::C       = SDLK_c;
    const u64 Keybd::D       = SDLK_d;
    const u64 Keybd::E       = SDLK_e;
    const u64 Keybd::F       = SDLK_f;
    const u64 Keybd::G       = SDLK_g;
    const u64 Keybd::H       = SDLK_h;
    const u64 Keybd::I       = SDLK_i;
    const u64 Keybd::J       = SDLK_j;
    const u64 Keybd::K       = SDLK_k;
    const u64 Keybd::L       = SDLK_l;
    const u64 Keybd::M       = SDLK_m;
    const u64 Keybd::N       = SDLK_n;
    const u64 Keybd::O       = SDLK_o;
    const u64 Keybd::P       = SDLK_p;
    const u64 Keybd::Q       = SDLK_q;
    const u64 Keybd::R       = SDLK_r;
    const u64 Keybd::S       = SDLK_s;
    const u64 Keybd::T       = SDLK_t;
    const u64 Keybd::U       = SDLK_u;
    const u64 Keybd::V       = SDLK_v;
    const u64 Keybd::W       = SDLK_w;
    const u64 Keybd::X       = SDLK_x;
    const u64 Keybd::Y       = SDLK_y;
    const u64 Keybd::Z       = SDLK_z;
    const u64 Keybd::UP      = SDLK_UP;
    const u64 Keybd::DOWN    = SDLK_DOWN;
    const u64 Keybd::LEFT    = SDLK_LEFT;
    const u64 Keybd::RIGHT   = SDLK_RIGHT;
    const u64 Keybd::ESC     = SDLK_ESCAPE;
    const u64 Keybd::CNTRL_L = SDLK_LCTRL;
    const u64 Keybd::CNTRL_R = SDLK_RCTRL;
    const u64 Keybd::SHIFT_L = SDLK_LSHIFT;
    const u64 Keybd::SHIFT_R = SDLK_RSHIFT;
    const u64 Keybd::ENTER_L = SDLK_RETURN;
    const u64 Keybd::ENTER_R = SDLK_RETURN2;
    const u64 Keybd::SYS_L   = SDLK_LGUI;
    const u64 Keybd::SYS_R   = SDLK_RGUI;
    const u64 Keybd::ALT_L   = SDLK_LALT;
    const u64 Keybd::ALT_R   = SDLK_RALT;

    bool
    is_keybd_press(u64 key)
    {
        u64 scan = keybd_get_scan(key);

        if ( scan < keybd_size )
            return keybd_data[scan] != 0;

        return false;
    }

    bool
    is_keybd_release(u64 key)
    {
        u64 scan = keybd_get_scan(key);

        if ( scan < keybd_size )
            return keybd_data[scan] == 0;

        return false;
    }

    u64
    keybd_get_scan(u64 key)
    {
        return SDL_GetScancodeFromKey(key);
    }

    const u64 Mouse::BTN_LEFT   = SDL_BUTTON_LEFT;
    const u64 Mouse::BTN_CENTRE = SDL_BUTTON_MIDDLE;
    const u64 Mouse::BTN_RIGHT  = SDL_BUTTON_RIGHT;

    v2s64
    mouse_coords()
    {
        v2s64 coords = {};

        SDL_GetMouseState(
            (s32*) &coords(0),
            (s32*) &coords(1)
        );

        return coords;
    }

    bool
    is_mouse_press(u64 btn)
    {
        return bits_test(SDL_GetMouseState(0, 0), btn);
    }

    bool
    is_mouse_release(u64 btn)
    {
        return bits_test(SDL_GetMouseState(0, 0), btn) == false;
    }
} // pax