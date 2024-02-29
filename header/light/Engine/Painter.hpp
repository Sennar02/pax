#ifndef LIGHT_ENGINE_PAINTER_HPP
#define LIGHT_ENGINE_PAINTER_HPP

#include <light/Engine/define.hpp>
#include <light/Engine/Display.hpp>

namespace light
{
    struct Painter
    {
    public:
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
        set_colour(v4u64 rgba = {});

        /**
         *
         */
        void
        fill_rect(v4f64 border);
    };
} // light

#endif // LIGHT_ENGINE_PAINTER_HPP
