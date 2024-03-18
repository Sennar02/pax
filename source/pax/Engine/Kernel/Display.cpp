#include <pax/Engine/Kernel/Display.hpp>

namespace pax
{
    const u64 Display::START_SHOW = SDL_WINDOW_SHOWN;
    const u64 Display::START_HIDE = SDL_WINDOW_HIDDEN;
    const u64 Display::START_MIN  = SDL_WINDOW_MINIMIZED;
    const u64 Display::START_MAX  = SDL_WINDOW_MAXIMIZED;
    const u64 Display::RESIZEABLE = SDL_WINDOW_RESIZABLE;
    const u64 Display::BORDERLESS = SDL_WINDOW_BORDERLESS;
    const u64 Display::ALWAYS_TOP = SDL_WINDOW_ALWAYS_ON_TOP;

    Display::Display() {}

    bool
    Display::is_valid() const
    {
        return data != 0;
    }

    bool
    Display::create(Screen& screen, v2u64 size, u32 flags)
    {
        u64 index = screen.index;

        if ( screen.is_valid() ) {
            data = SDL_CreateWindow("",
                SDL_WINDOWPOS_CENTERED_DISPLAY(index),
                SDL_WINDOWPOS_CENTERED_DISPLAY(index),
                size[0], size[1], flags
            );
        }

        return data != 0;
    }

    bool
    Display::create(Screen& screen, v2u64 size, String title, u32 flags)
    {
        u64 index = screen.index;

        if ( screen.is_valid() ) {
            data = SDL_CreateWindow(title.data,
                SDL_WINDOWPOS_CENTERED_DISPLAY(index),
                SDL_WINDOWPOS_CENTERED_DISPLAY(index),
                size[0], size[1], flags
            );
        }

        return data != 0;
    }

    Display&
    Display::destroy()
    {
        if ( data != 0 )
            SDL_DestroyWindow(data);

        data = 0;

        return *this;
    }

    Display&
    Display::set_title(String title)
    {
        if ( data != 0 )
            SDL_SetWindowTitle(data, title.data);

        return *this;
    }
} // pax
