#include <light/Engine/Events/Event_System_Source.hpp>

namespace light
{
    Keybd_Event
    from_sdl(SDL_KeyboardEvent event)
    {
        Keybd_Event keybd;

        keybd.physic = event.keysym.scancode;
        keybd.symbol = event.keysym.sym;
        keybd.modifs = event.keysym.mod;

        keybd.flags =
            bits_write(keybd.flags, Keybd_Event::REPEAT, event.repeat != 0) |
            bits_write(keybd.flags, Keybd_Event::PRESS, event.state == SDL_PRESSED);

        return keybd;
    }

    Mouse_Event
    from_sdl(SDL_MouseMotionEvent event)
    {
        Mouse_Event mouse;
        u64         flags = 0;

        flags = SDL_GetMouseState((s32*) &mouse.coords[0], (s32*) &mouse.coords[1]);

        mouse.motion = {event.xrel, event.yrel};
        mouse.flags =
            bits_write(mouse.flags, Mouse_Event::MAIN_L, flags & SDL_BUTTON_LMASK) |
            bits_write(mouse.flags, Mouse_Event::MAIN_M, flags & SDL_BUTTON_MMASK) |
            bits_write(mouse.flags, Mouse_Event::MAIN_R, flags & SDL_BUTTON_RMASK) |
            bits_write(mouse.flags, Mouse_Event::EXTR_1, flags & SDL_BUTTON_X1MASK) |
            bits_write(mouse.flags, Mouse_Event::EXTR_2, flags & SDL_BUTTON_X2MASK);

        return mouse;
    }

    Mouse_Event
    from_sdl(SDL_MouseButtonEvent event)
    {
        Mouse_Event mouse;
        u64         flags = 0;

        flags = SDL_GetMouseState((s32*) &mouse.coords[0], (s32*) &mouse.coords[1]);

        mouse.button = event.button;
        mouse.flags =
            bits_write(mouse.flags, Mouse_Event::PRESS, event.state == SDL_PRESSED) |
            bits_write(mouse.flags, Mouse_Event::MAIN_L, flags & SDL_BUTTON_LMASK) |
            bits_write(mouse.flags, Mouse_Event::MAIN_M, flags & SDL_BUTTON_MMASK) |
            bits_write(mouse.flags, Mouse_Event::MAIN_R, flags & SDL_BUTTON_RMASK) |
            bits_write(mouse.flags, Mouse_Event::EXTR_1, flags & SDL_BUTTON_X1MASK) |
            bits_write(mouse.flags, Mouse_Event::EXTR_2, flags & SDL_BUTTON_X2MASK);

        return mouse;
    }

    Mouse_Event
    from_sdl(SDL_MouseWheelEvent event)
    {
        Mouse_Event mouse;
        u64         flags = 0;

        flags = SDL_GetMouseState((s32*) &mouse.coords[0], (s32*) &mouse.coords[1]);

        mouse.scroll = {event.preciseX, event.preciseY};
        mouse.scroll = mouse.scroll * (
            (event.direction == SDL_MOUSEWHEEL_NORMAL) -
            (event.direction == SDL_MOUSEWHEEL_FLIPPED)
        );

        mouse.flags =
            bits_write(mouse.flags, Mouse_Event::MAIN_L, flags & SDL_BUTTON_LMASK) |
            bits_write(mouse.flags, Mouse_Event::MAIN_M, flags & SDL_BUTTON_MMASK) |
            bits_write(mouse.flags, Mouse_Event::MAIN_R, flags & SDL_BUTTON_RMASK) |
            bits_write(mouse.flags, Mouse_Event::EXTR_1, flags & SDL_BUTTON_X1MASK) |
            bits_write(mouse.flags, Mouse_Event::EXTR_2, flags & SDL_BUTTON_X2MASK);

        return mouse;
    }

    void
    Event_System_Source::provide(Dispatcher& dispat)
    {
        SDL_Event event;

        while ( SDL_PollEvent(&event) != 0 ) {
            switch ( event.type ) {
                case SDL_KEYDOWN:         light_excl( dispat.publish(from_sdl(event.key));    );
                case SDL_KEYUP:           light_excl( dispat.publish(from_sdl(event.key));    );
                case SDL_MOUSEMOTION:     light_excl( dispat.publish(from_sdl(event.motion)); );
                case SDL_MOUSEBUTTONDOWN: light_excl( dispat.publish(from_sdl(event.button)); );
                case SDL_MOUSEBUTTONUP:   light_excl( dispat.publish(from_sdl(event.button)); );
                case SDL_MOUSEWHEEL:      light_excl( dispat.publish(from_sdl(event.wheel));  );
            }
        }
    }
} // light
