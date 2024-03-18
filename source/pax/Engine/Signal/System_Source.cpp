#include <pax/Engine/Signal/System_Source.hpp>

namespace pax
{
    Keybd_Signal
    from_sdl(SDL_KeyboardEvent event)
    {
        Keybd_Signal keybd;

        keybd.physic = event.keysym.scancode;
        keybd.symbol = event.keysym.sym;
        keybd.modifs = event.keysym.mod;

        keybd.flags =
            bits_write(keybd.flags, Keybd_Signal::FLAG_REPEAT, event.repeat != 0) |
            bits_write(keybd.flags, Keybd_Signal::FLAG_PRESS, event.state == SDL_PRESSED);

        return keybd;
    }

    Mouse_Signal
    from_sdl(SDL_MouseMotionEvent event)
    {
        Mouse_Signal mouse;
        u64         flags = 0;

        flags = SDL_GetMouseState((s32*) &mouse.coords[0], (s32*) &mouse.coords[1]);

        mouse.motion = {event.xrel, event.yrel};
        mouse.flags =
            bits_write(mouse.flags, Mouse_Signal::FLAG_BTN_L, flags & SDL_BUTTON_LMASK) |
            bits_write(mouse.flags, Mouse_Signal::FLAG_BTN_M, flags & SDL_BUTTON_MMASK) |
            bits_write(mouse.flags, Mouse_Signal::FLAG_BTN_R, flags & SDL_BUTTON_RMASK) |
            bits_write(mouse.flags, Mouse_Signal::FLAG_BTN_X, flags & SDL_BUTTON_X1MASK) |
            bits_write(mouse.flags, Mouse_Signal::FLAG_BTN_Y, flags & SDL_BUTTON_X2MASK);

        return mouse;
    }

    Mouse_Signal
    from_sdl(SDL_MouseButtonEvent event)
    {
        Mouse_Signal mouse;
        u64         flags = 0;

        flags = SDL_GetMouseState((s32*) &mouse.coords[0], (s32*) &mouse.coords[1]);

        mouse.button = event.button;
        mouse.flags =
            bits_write(mouse.flags, Mouse_Signal::FLAG_PRESS, event.state == SDL_PRESSED) |
            bits_write(mouse.flags, Mouse_Signal::FLAG_BTN_L, flags & SDL_BUTTON_LMASK) |
            bits_write(mouse.flags, Mouse_Signal::FLAG_BTN_M, flags & SDL_BUTTON_MMASK) |
            bits_write(mouse.flags, Mouse_Signal::FLAG_BTN_R, flags & SDL_BUTTON_RMASK) |
            bits_write(mouse.flags, Mouse_Signal::FLAG_BTN_X, flags & SDL_BUTTON_X1MASK) |
            bits_write(mouse.flags, Mouse_Signal::FLAG_BTN_Y, flags & SDL_BUTTON_X2MASK);

        return mouse;
    }

    Mouse_Signal
    from_sdl(SDL_MouseWheelEvent event)
    {
        Mouse_Signal mouse;
        u64         flags = 0;

        flags = SDL_GetMouseState((s32*) &mouse.coords[0], (s32*) &mouse.coords[1]);

        mouse.scroll = {event.preciseX, event.preciseY};
        mouse.scroll = mouse.scroll * (
            (event.direction == SDL_MOUSEWHEEL_NORMAL) -
            (event.direction == SDL_MOUSEWHEEL_FLIPPED)
        );

        mouse.flags =
            bits_write(mouse.flags, Mouse_Signal::FLAG_BTN_L, flags & SDL_BUTTON_LMASK) |
            bits_write(mouse.flags, Mouse_Signal::FLAG_BTN_M, flags & SDL_BUTTON_MMASK) |
            bits_write(mouse.flags, Mouse_Signal::FLAG_BTN_R, flags & SDL_BUTTON_RMASK) |
            bits_write(mouse.flags, Mouse_Signal::FLAG_BTN_X, flags & SDL_BUTTON_X1MASK) |
            bits_write(mouse.flags, Mouse_Signal::FLAG_BTN_Y, flags & SDL_BUTTON_X2MASK);

        return mouse;
    }

    Display_Signal
    from_sdl(u64 flags)
    {
        Display_Signal display;

        display.flags = flags;

        return display;
    }

    bool
    System_Source::provide(Dispatcher& dispat)
    {
        SDL_Event event;

        if ( SDL_PollEvent(&event) != 0 ) {
            switch ( event.type ) {
                case SDL_KEYDOWN:         pax_excl({ dispat.publish(from_sdl(event.key));    });
                case SDL_KEYUP:           pax_excl({ dispat.publish(from_sdl(event.key));    });
                case SDL_MOUSEMOTION:     pax_excl({ dispat.publish(from_sdl(event.motion)); });
                case SDL_MOUSEBUTTONDOWN: pax_excl({ dispat.publish(from_sdl(event.button)); });
                case SDL_MOUSEBUTTONUP:   pax_excl({ dispat.publish(from_sdl(event.button)); });
                case SDL_MOUSEWHEEL:      pax_excl({ dispat.publish(from_sdl(event.wheel));  });
                case SDL_QUIT:            pax_excl({ dispat.publish(from_sdl(Display_Signal::FLAG_CLOSE)); });
            }

            return true;
        }

        return false;
    }
} // pax
