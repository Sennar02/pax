#include <light/Engine/Painter.hpp>

namespace light
{
    Painter::Painter()
        : data {0}
    {}

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
    Painter::swap()
    {
        SDL_RenderClear(data);
    }

    void
    Painter::show()
    {
        SDL_RenderPresent(data);
    }

    void
    Painter::set_colour(Vec4u rgba)
    {
        SDL_SetRenderDrawColor(data,
            rgba[0], rgba[1],
            rgba[2], rgba[3]
        );
    }

    void
    Painter::draw_rect_full(Vec4f rect)
    {
        SDL_Rect helper = {
            (s32) rect[0], // x
            (s32) rect[1], // y
            (s32) rect[2], // w
            (s32) rect[3], // h
        };

        SDL_RenderFillRect(data, &helper);
    }
} // light
