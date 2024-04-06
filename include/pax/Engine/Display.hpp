#ifndef PAX_ENGINE_DISPLAY_HPP
#define PAX_ENGINE_DISPLAY_HPP

#include <pax/Engine/define.hpp>
#include <pax/Engine/Monitor.hpp>

struct SDL_Window;

namespace pax
{
    struct Display
    {
    public:
        static const u64 START_SHOW;
        static const u64 START_HIDE;
        static const u64 START_MIN;
        static const u64 START_MAX;
        static const u64 RESIZEABLE;
        static const u64 BORDERLESS;
        static const u64 ALWAYS_TOP;

    public:
        /**
         * Internal pointer.
         */
        SDL_Window* data = 0;

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
        acquire(Monitor& screen, v2f64 size, u32 flags = 0);

        /**
         * todo: Comment.
         */
        bool
        acquire(Monitor& screen, String title, v2f64 size, u32 flags = 0);

        /**
         * todo: Comment.
         */
        Display&
        release();

        /**
         * todo: Comment.
         */
        Display&
        set_position(v2f64 position);

        /**
         * todo: Comment.
         */
        Display&
        set_title(String title);
    };
} // pax

#endif // PAX_ENGINE_DISPLAY_HPP