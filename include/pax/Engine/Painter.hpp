#ifndef PAX_ENGINE_PAINTER_HPP
#define PAX_ENGINE_PAINTER_HPP

#include <pax/Engine/define.hpp>
#include <pax/Engine/Display.hpp>

struct SDL_Renderer;

namespace pax
{
    /**
     *  todo: Comment.
     */
    using Colour = Vec4d<u8>;

    struct Blend_Mode
    {
        static const u64 NONE;
        static const u64 BLEND;
        static const u64 ADD;
        static const u64 MOD;
        static const u64 MUL;
    };

    struct Painter
    {
    public:
        /**
         * todo: Comment.
         */
        SDL_Renderer* data = 0;

    public:

        /**
         * todo: Comment.
         */
        bool
        is_valid() const;

        /**
         * todo: Comment.
         */
        bool
        acquire(Display& display);

        /**
         * todo: Comment.
         */
        void
        release();

        /**
         * todo: Comment.
         */
        void
        clear();

        /**
         * todo: Comment.
         */
        void
        paint();

        /**
         * todo: Comment.
         */
        void
        set_scale(v2f64 factor);

        /**
         * todo: Comment.
         */
        void
        set_colour(Colour rgba = {});

        /**
         * todo: Comment.
         */
        void
        set_blend_mode(u64 mode);

        /**
         * todo: Comment.
         */
        void
        paint_rect_fill(v4f64 border);
    };
} // pax

#endif // PAX_ENGINE_PAINTER_HPP