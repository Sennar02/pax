#include <light/Engine/Events/Keybd_Event.hpp>

namespace light
{
    const u64 Keybd_Event::KIND = Event_Kind::KEYBD;
    const u64 Keybd_Event::MASK = Event_Flags::INPUT;

    u64
    Keybd_Event::kind() const
    {
        return Keybd_Event::KIND;
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
} // light
