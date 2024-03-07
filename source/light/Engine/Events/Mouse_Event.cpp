#include <light/Engine/Events/Mouse_Event.hpp>

namespace light
{
    const u64 Mouse_Event::KIND = Event_Kind::MOUSE;

    u64
    Mouse_Event::kind() const
    {
        return Event_Kind::MOUSE;
    }

    u64
    Mouse_Event::mask() const
    {
        return Event_Flags::INPUT;
    }

    bool
    Mouse_Event::is_press() const
    {
        return bits_test(flags, PRESS);
    }

    bool
    Mouse_Event::is_release() const
    {
        return bits_test(flags, PRESS) == false;
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
} // light
