#include <light/Engine/Event.hpp>

namespace light
{
    const u64 Keybd_Press_Event::TYPE = KEYBD_PRESS;

    u64
    Keybd_Press_Event::type() const
    {
        return TYPE;
    }

    u64
    Keybd_Press_Event::mask() const
    {
        return 0;
    }

    const u64 Keybd_Release_Event::TYPE = KEYBD_RELEASE;

    u64
    Keybd_Release_Event::type() const
    {
        return TYPE;
    }

    u64
    Keybd_Release_Event::mask() const
    {
        return 0;
    }
} // light
