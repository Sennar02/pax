#ifndef LIGHT_ENGINE_PAINTER_HPP
#define LIGHT_ENGINE_PAINTER_HPP

#include <light/Engine/define.hpp>
#include <light/Engine/Display.hpp>

namespace light
{
    struct Painter
    {
    private:
        /**
         *
         */
        SDL_Renderer* data;

    public:
        /**
         *
         */
        Painter();

        /**
         *
         */
        bool
        is_valid() const;

        /**
         *
         */
        bool
        create(Display& display);

        /**
         *
         */
        void
        destroy();

        /**
         *
         */
        void
        swap();

        /**
         *
         */
        void
        show();

        /**
         *
         */
        void
        set_colour(Vec4u rgba);

        /**
         *
         */
        void
        draw_rect_full(Vec4f rect);
    };
} // light

#endif // LIGHT_ENGINE_PAINTER_HPP
