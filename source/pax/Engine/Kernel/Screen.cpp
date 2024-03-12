#include <pax/Engine/Kernel/Screen.hpp>

namespace pax
{
    bool
    Screen::is_valid() const
    {
        return index < (u64) SDL_GetNumVideoDisplays();
    }

    v2u64
    Screen::size() const
    {
        SDL_Rect rect;

        if ( SDL_GetDisplayUsableBounds(index, &rect) != 0 )
            return {};

        return {
            (u64) rect.w,
            (u64) rect.h,
        };
    }

    v4u64
    Screen::bounds() const
    {
        SDL_Rect rect;

        if ( SDL_GetDisplayBounds(index, &rect) != 0 )
            return {};

        return {
            (u64) rect.x,
            (u64) rect.y,
            (u64) rect.w,
            (u64) rect.h,
        };
    }
} // pax
