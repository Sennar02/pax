#ifndef LIGHT_ENGINE_EVENT_SYSTEM_SOURCE_HPP
#define LIGHT_ENGINE_EVENT_SYSTEM_SOURCE_HPP

#include <light/Events/Dispatcher.hpp>
#include <light/Engine/Events/Keybd_Event.hpp>
#include <light/Engine/Events/Mouse_Event.hpp>

namespace light
{
    struct Event_System_Source
    {
    public:
        /**
         *
         */
        void
        provide(Dispatcher& dispat);
    };
} // light

#endif // LIGHT_ENGINE_EVENT_SYSTEM_SOURCE_HPP
