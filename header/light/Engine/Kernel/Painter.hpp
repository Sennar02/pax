#ifndef LIGHT_ENGINE_PAINTER_HPP
#define LIGHT_ENGINE_PAINTER_HPP

#include <light/Engine/define.hpp>
#include <light/Engine/Kernel/Display.hpp>

namespace light
{
    struct Painter
    {
    public:
        enum Blend_Mode
        {
            NONE  = SDL_BLENDMODE_NONE,
            BLEND = SDL_BLENDMODE_BLEND,
            ADD   = SDL_BLENDMODE_ADD,
            MOD   = SDL_BLENDMODE_MOD,
            MUL   = SDL_BLENDMODE_MUL,
        };

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
        prepare();

        /**
         *
         */
        void
        present();

        /**
         *
         */
        void
        scale(f64 factor);

        /**
         *
         */
        void
        set_colour(v4u64 rgba = {});

        /**
         *
         */
        void
        set_blend_mode(Blend_Mode mode);

        /**
         *
         */
        void
        fill_rect(v4f64 border);
    };
} // light

#endif // LIGHT_ENGINE_PAINTER_HPP
