#include <pax/Engine/Painter.hpp>

// SDL_CreateRenderer, SDL_DestroyRenderer, SDL_RenderClear,
// SDL_RenderPresent, SDL_RenderSetScale, SDL_SetRenderDrawColor,
// SDL_SEtRenderDrawBlendMode, SDL_RenderFillRect.
#include <SDL2/SDL_render.h>

namespace pax
{
    const u64 Blend_Mode::NONE  = SDL_BLENDMODE_NONE;
    const u64 Blend_Mode::BLEND = SDL_BLENDMODE_BLEND;
    const u64 Blend_Mode::ADD   = SDL_BLENDMODE_ADD;
    const u64 Blend_Mode::MOD   = SDL_BLENDMODE_MOD;
    const u64 Blend_Mode::MUL   = SDL_BLENDMODE_MUL;

    bool
    Painter::is_valid() const
    {
        return data != 0;
    }

    bool
    Painter::acquire(Display& display)
    {
        if ( display.is_valid() == false )
            return false;

        data = SDL_CreateRenderer(display.data,
            -1, SDL_RENDERER_ACCELERATED
        );

        return data != 0;
     }

    void
    Painter::release()
    {
        if ( data != 0 )
            SDL_DestroyRenderer(data);

        data = 0;
    }

    void
    Painter::clear()
    {
        SDL_RenderClear(data);
    }

    void
    Painter::paint()
    {
        SDL_RenderPresent(data);
    }

    void
    Painter::set_scale(v2f64 scale)
    {
        if ( data != 0 )
            SDL_RenderSetScale(data, scale(0), scale(1));
    }

    void
    Painter::set_colour(Colour rgba)
    {
        SDL_SetRenderDrawColor(data,
            rgba(0), rgba(1),
            rgba(2), rgba(3)
        );
    }

    void
    Painter::set_blend_mode(u64 mode)
    {
        SDL_SetRenderDrawBlendMode(data, (SDL_BlendMode) mode);
    }

    void
    Painter::paint_rect_fill(v4f64 border)
    {
        SDL_Rect rect = {
            (s32) border(0), // x
            (s32) border(1), // y
            (s32) border(2), // w
            (s32) border(3), // h
        };

        SDL_RenderFillRect(data, &rect);
    }
} // pax