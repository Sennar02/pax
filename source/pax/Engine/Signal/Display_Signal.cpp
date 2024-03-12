#include <pax/Engine/Signal/Display_Signal.hpp>

namespace pax
{
    const u64 Display_Signal::KIND = Signal_Kind::DISPLAY;

    u64
    Display_Signal::kind() const
    {
        return Display_Signal::KIND;
    }

    bool
    Display_Signal::is_close() const
    {
        return bits_test(flags, FLAG_CLOSE);
    }
} // pax
