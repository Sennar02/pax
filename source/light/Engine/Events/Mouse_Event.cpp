#include <light/Engine/Events/Mouse_Event.hpp>

namespace light
{
    const u64 Mouse_Event::KIND = Event_Kind::MOUSE;
    const u64 Mouse_Event::MASK = Event_Flags::INPUT;

    u64
    Mouse_Event::kind() const
    {
        return Mouse_Event::KIND;
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
} // light
