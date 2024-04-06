#include <pax/Engine/Monitor.hpp>

// SDL_GetNumVideoDisplays, SDL_GetDisplayUsableBounds,
// SDL_GetDisplayBounds.
#include <SDL2/SDL_video.h>

namespace pax
{
    bool
    Monitor::is_valid() const
    {
        return index < (u64) SDL_GetNumVideoDisplays();
    }

    v2u64
    Monitor::size() const
    {
        SDL_Rect rect;
        v2u64    value = {};

        if ( SDL_GetDisplayUsableBounds(index, &rect) == 0 )
            value = {(u64) rect.w, (u64) rect.h};

        return value;
    }

    v4u64
    Monitor::bounds() const
    {
        SDL_Rect rect;
        v4u64    value = {};

        if ( SDL_GetDisplayBounds(index, &rect) == 0 ) {
            value = {
                (u64) rect.x, (u64) rect.y,
                (u64) rect.w, (u64) rect.h,
            };
        }

        return value;
    }
} // pax