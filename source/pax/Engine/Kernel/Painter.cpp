#include <pax/Engine/Kernel/Painter.hpp>

namespace pax
{
    enum Blend_Mode : u32
    {
        NONE  = SDL_BLENDMODE_NONE,
        BLEND = SDL_BLENDMODE_BLEND,
        ADD   = SDL_BLENDMODE_ADD,
        MOD   = SDL_BLENDMODE_MOD,
        MUL   = SDL_BLENDMODE_MUL,
    };

    Painter::Painter() {}

    bool
    Painter::is_valid() const
    {
        return data != 0;
    }

    bool
    Painter::create(Display& display)
    {
        if ( display.is_valid() == false )
            return false;

        data = SDL_CreateRenderer(display.data,
            -1, SDL_RENDERER_ACCELERATED
        );

        return data != 0;
     }

    void
    Painter::destroy()
    {
        if ( data != 0 )
            SDL_DestroyRenderer(data);

        data = 0;
    }

    void
    Painter::prepare()
    {
        SDL_RenderClear(data);
    }

    void
    Painter::present()
    {
        SDL_RenderPresent(data);
    }

    void
    Painter::scale(f64 factor)
    {
        SDL_RenderSetScale(data, factor, factor);
    }

    void
    Painter::set_colour(v4u64 rgba)
    {
        SDL_SetRenderDrawColor(data,
            rgba[0], rgba[1],
            rgba[2], rgba[3]
        );
    }

    void
    Painter::set_blend_mode(Blend_Mode mode)
    {
        SDL_SetRenderDrawBlendMode(data, (SDL_BlendMode) mode);
    }

    void
    Painter::fill_rect(v4f64 border)
    {
        SDL_Rect rect = {
            (s32) border[0], // x
            (s32) border[1], // y
            (s32) border[2], // w
            (s32) border[3], // h
        };

        SDL_RenderFillRect(data, &rect);
    }
} // pax
