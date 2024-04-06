#include <pax/Engine/Display.hpp>
#include <pax/Engine/Monitor.hpp>

// SDL_CreateWindow, SDL_DestroyWindow, SDL_SetWindowTitle.
#include <SDL2/SDL_video.h>

#define pax_display_center(index) \
    SDL_WINDOWPOS_CENTERED_DISPLAY(index)

namespace pax
{
    const u64 Display::START_SHOW = SDL_WINDOW_SHOWN;
    const u64 Display::START_HIDE = SDL_WINDOW_HIDDEN;
    const u64 Display::START_MIN  = SDL_WINDOW_MINIMIZED;
    const u64 Display::START_MAX  = SDL_WINDOW_MAXIMIZED;
    const u64 Display::RESIZEABLE = SDL_WINDOW_RESIZABLE;
    const u64 Display::BORDERLESS = SDL_WINDOW_BORDERLESS;
    const u64 Display::ALWAYS_TOP = SDL_WINDOW_ALWAYS_ON_TOP;

    bool
    Display::is_valid() const
    {
        return data != 0;
    }

    bool
    Display::acquire(Monitor& monitor, v2f64 size, u32 flags)
    {
        u64 index = monitor.index;

        if ( monitor.is_valid() ) {
            data = SDL_CreateWindow("",
                pax_display_center(index),
                pax_display_center(index),
                (u64) size(0),
                (u64) size(1),
                flags
            );
        }

        return data != 0;
    }

    bool
    Display::acquire(Monitor& monitor, String title, v2f64 size, u32 flags)
    {
        u64 index = monitor.index;

        if ( monitor.is_valid() ) {
            data = SDL_CreateWindow(title.data,
                pax_display_center(index),
                pax_display_center(index),
                (u64) size(0),
                (u64) size(1),
                flags
            );
        }

        return data != 0;
    }

    Display&
    Display::release()
    {
        if ( data != 0 )
            SDL_DestroyWindow(data);

        data = 0;

        return pax_self;
    }

    Display&
    Display::set_position(v2f64 position)
    {
        if ( data != 0 )
            SDL_SetWindowPosition(data, (u64) position(0), (u64) position(1));

        return pax_self;
    }

    Display&
    Display::set_title(String title)
    {
        if ( data != 0 )
            SDL_SetWindowTitle(data, title.data);

        return pax_self;
    }
} // pax