#include <pax/Engine/Signal/Mouse_Signal.hpp>

namespace pax
{
    const u64 Mouse_Signal::KIND = Signal_Kind::MOUSE;

    u64
    Mouse_Signal::kind() const
    {
        return Mouse_Signal::KIND;
    }

    bool
    Mouse_Signal::is_press() const
    {
        return bits_test(flags, FLAG_PRESS);
    }

    bool
    Mouse_Signal::is_release() const
    {
        return bits_test(flags, FLAG_PRESS) == false;
    }

    bool
    Mouse_Signal::test_btn(u64 index) const
    {
        if ( index >= FLAG_BTN_L && index <= FLAG_BTN_Y )
            return bits_test(flags, index);

        return false;
    }
} // pax
