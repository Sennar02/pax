#ifndef LIGHT_ENGINE_EVENT_QUEUE_HPP
#define LIGHT_ENGINE_EVENT_QUEUE_HPP

#include <light/Engine/Events/Event_Broker.hpp>
#include <light/Engine/Events/Keybd_Event.hpp>
#include <light/Engine/Events/Mouse_Event.hpp>

namespace light
{
    struct Event_Queue
    {
    public:
        /**
         *
         */
        void
        dequeue(Event_Broker& broker);
    };
} // light

#endif // LIGHT_ENGINE_EVENT_QUEUE_HPP
