#ifndef LIGHT_EVENTS_EVENT_HPP
#define LIGHT_EVENTS_EVENT_HPP

#include <light/Events/define.hpp>

namespace light
{
    enum Event_Kind
    {
        DISPLAY = 1,
        KEYBD   = 2,
        MOUSE   = 3,
    };

    enum Event_Flags
    {
        INPUT  = 0x01,
        OUTPUT = 0x02,
    };

    struct Event
    {
    public:
        /**
         *
         */
        virtual u64
        kind() const = 0;
    };
} // light

#endif // LIGHT_EVENTS_EVENT_HPP
