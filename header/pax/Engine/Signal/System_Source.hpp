#ifndef PAX_ENGINE_EVENT_SYSTEM_SOURCE_HPP
#define PAX_ENGINE_EVENT_SYSTEM_SOURCE_HPP

#include <pax/Engine/define.hpp>
#include <pax/Engine/Signal/Keybd_Signal.hpp>
#include <pax/Engine/Signal/Mouse_Signal.hpp>
#include <pax/Engine/Signal/Display_Signal.hpp>

namespace pax
{
    struct System_Source
        : public Source
    {
    public:
        /**
         *
         */
        bool
        provide(Dispatcher& dispat);
    };

    static System_Source system_src;
} // pax

#endif // PAX_ENGINE_EVENT_SYSTEM_SOURCE_HPP
