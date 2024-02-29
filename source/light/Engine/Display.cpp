#include <light/Engine/Display.hpp>

namespace light
{
    Display::Display()
        : data {0}
    {}

    bool
    Display::is_valid() const
    {
        return data != 0;
    }

    bool
    Display::create(String title, v2u64 size, u32 flags)
    {
        data = SDL_CreateWindow(title.data,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            size[0], size[1], flags
        );

        return data != 0;
    }

    void
    Display::destroy()
    {
        if ( data != 0 )
            SDL_DestroyWindow(data);

        data = 0;
    }
} // light
