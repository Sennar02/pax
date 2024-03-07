#include <light/Engine/Events/Keybd_Event.hpp>

namespace light
{
    const u64 Keybd_Event::KIND = Event_Kind::KEYBD;

    u64
    Keybd_Event::kind() const
    {
        return Event_Kind::KEYBD;
    }

    u64
    Keybd_Event::mask() const
    {
        return Event_Flags::INPUT;
    }

    bool
    Keybd_Event::is_repeat() const
    {
        return bits_test(flags, REPEAT);
    }

    bool
    Keybd_Event::is_press() const
    {
        return bits_test(flags, PRESS);
    }

    bool
    Keybd_Event::is_release() const
    {
        return bits_test(flags, PRESS) == false;
    }

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
} // light
