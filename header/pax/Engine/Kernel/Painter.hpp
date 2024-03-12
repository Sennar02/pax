#ifndef PAX_ENGINE_PAINTER_HPP
#define PAX_ENGINE_PAINTER_HPP

#include <pax/Engine/define.hpp>
#include <pax/Engine/Kernel/Display.hpp>

namespace pax
{
    enum Blend_Mode : u32;

    struct Painter
    {
    public:
        // /**
        //  *
        //  */
        // enum Blend_Mode
        // {
        //     NONE  = Blend_Mode_Impl::NONE,
        //     BLEND = Blend_Mode_Impl::BLEND,
        //     ADD   = Blend_Mode_Impl::ADD,
        //     MOD   = Blend_Mode_Impl::MOD,
        //     MUL   = Blend_Mode_Impl::MUL,
        // };

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
} // pax

#endif // PAX_ENGINE_PAINTER_HPP
