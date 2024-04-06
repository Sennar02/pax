#include <pax/Engine/Events.hpp>
#include <pax/Engine/Inputs.hpp>
#include <SDL2/SDL_events.h>

namespace pax
{
    const u64 Display_Event::SIGNAL_TYPE = Events::DISPLAY;
    const u64 Display_Event::FLAGS_CLOSE = 1u;

    bool
    Display_Event::is_close() const
    {
        return bits_test(flags, Display_Event::FLAGS_CLOSE);
    }

    const u64 Keybd_Event::SIGNAL_TYPE  = Events::KEYBOARD;
    const u64 Keybd_Event::FLAGS_REPEAT = 1u;
    const u64 Keybd_Event::FLAGS_PRESS  = 2u;

    bool
    Keybd_Event::is_repeat() const
    {
        return bits_test(flags, Keybd_Event::FLAGS_REPEAT);
    }

    bool
    Keybd_Event::is_press() const
    {
        return bits_test(flags, Keybd_Event::FLAGS_PRESS);
    }

    bool
    Keybd_Event::is_release() const
    {
        return bits_test(flags, Keybd_Event::FLAGS_PRESS) == false;
    }

    const u64 Mouse_Event::SIGNAL_TYPE = Events::MOUSE;
    const u64 Mouse_Event::FLAGS_PRESS = 1u;

    bool
    Mouse_Event::is_repeat() const
    {
        return clicks >= 2u;
    }

    bool
    Mouse_Event::is_press() const
    {
        return bits_test(flags, Mouse_Event::FLAGS_PRESS);
    }

    bool
    Mouse_Event::is_release() const
    {
        return bits_test(flags, Mouse_Event::FLAGS_PRESS) == false;
    }

    Keybd_Event
    convert(SDL_KeyboardEvent event)
    {
        Keybd_Event value;

        value.code   = event.keysym.sym;
        value.modifs = event.keysym.mod;
        value.flags  = (Keybd_Event::FLAGS_REPEAT * (event.repeat != 0))
                     | (Keybd_Event::FLAGS_PRESS  * (event.state == SDL_PRESSED));

        return value;
    }

    Mouse_Event
    convert(SDL_MouseMotionEvent event)
    {
        Mouse_Event value;

        value.coords = mouse_coords();
        value.motion = {event.xrel, event.yrel};

        return value;
    }

    Mouse_Event
    convert(SDL_MouseButtonEvent event)
    {
        Mouse_Event value;

        value.coords = mouse_coords();
        value.button = event.button;
        value.flags  = (Mouse_Event::FLAGS_PRESS * (event.state == SDL_PRESSED));

        return value;
    }

    Mouse_Event
    convert(SDL_MouseWheelEvent event)
    {
        Mouse_Event value;

        value.coords = mouse_coords();
        value.scroll = {event.x, event.y};
        value.orient = (event.direction == SDL_MOUSEWHEEL_NORMAL)
                     - (event.direction == SDL_MOUSEWHEEL_FLIPPED);

        return value;
    }

    Display_Event
    convert(SDL_QuitEvent)
    {
        Display_Event value;

        value.flags = bits_write(value.flags, Display_Event::FLAGS_CLOSE);

        return value;
    }

    bool
    event_poll(Dispatcher& dispat)
    {
        SDL_Event event;

        if ( SDL_PollEvent(&event) != 0 ) {
            switch ( event.type ) {
                pax_case_excl(SDL_KEYDOWN,         { dispat.publish( convert(event.key) ); });
                pax_case_excl(SDL_KEYUP,           { dispat.publish( convert(event.key) ); });
                pax_case_excl(SDL_MOUSEMOTION,     { dispat.publish( convert(event.motion) ); });
                pax_case_excl(SDL_MOUSEBUTTONDOWN, { dispat.publish( convert(event.button) ); });
                pax_case_excl(SDL_MOUSEBUTTONUP,   { dispat.publish( convert(event.button) ); });
                pax_case_excl(SDL_MOUSEWHEEL,      { dispat.publish( convert(event.wheel) ); });
                pax_case_excl(SDL_QUIT,            { dispat.publish( convert(event.quit) ); });
            }

            return true;
        }

        return false;
    }

    void
    event_update()
    {
        SDL_PumpEvents();
    }
} // pax
