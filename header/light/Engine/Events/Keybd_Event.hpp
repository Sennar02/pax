#ifndef LIGHT_ENGINE_KEYBD_EVENT_HPP
#define LIGHT_ENGINE_KEYBD_EVENT_HPP

#include <light/Engine/define.hpp>
#include <light/Engine/Events/Event.hpp>

namespace light
{
    struct Keybd_Event
        : public Event
    {
    public:
        /**
         *
         */
        static const u64 KIND;

    public:
        u64 physic = 0;
        u64 symbol = 0;
        u64 modifs = 0;
        u64 flags  = 0;

        enum Flags {
            REPEAT  = 0x01,
            PRESS   = 0x02,
        };

    public:
        /**
         *
         */
        u64
        kind() const;

        /**
         *
         */
        u64
        mask() const;

        /**
         *
         */
        bool
        is_repeat() const;

        /**
         *
         */
        bool
        is_press() const;

        /**
         *
         */
        bool
        is_release() const;
    };

    Keybd_Event
    from_sdl(SDL_KeyboardEvent event);
} // light

#endif // LIGHT_ENGINE_KEYBD_EVENT_HPP
