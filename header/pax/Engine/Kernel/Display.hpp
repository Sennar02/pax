#ifndef PAX_ENGINE_DISPLAY_HPP
#define PAX_ENGINE_DISPLAY_HPP

#include <pax/Engine/define.hpp>
#include <pax/Engine/Kernel/Screen.hpp>

namespace pax
{
    struct Display
    {
    public:
        pax_opt(u64, START_FULL);
        pax_opt(u64, START_SHOW);
        pax_opt(u64, START_HIDE);
        pax_opt(u64, START_MIN);
        pax_opt(u64, START_MAX);
        pax_opt(u64, RESIZEABLE);
        pax_opt(u64, BORDERLESS);
        pax_opt(u64, ALWAYS_TOP);

    public:
        /**
         * Internal pointer.
         */
        SDL_Window* data = 0;

    public:
        /**
         * Default constructor.
         */
        Display();

        /**
         *
         */
        bool
        is_valid() const;

        /**
         *
         */
        bool
        create(Screen& screen, v2u64 size, u32 flags = 0);

        /**
         *
         */
        bool
        create(Screen& screen, v2u64 size, String title, u32 flags = 0);

        /**
         *
         */
        Display&
        destroy();

        /**
         *
         */
        Display&
        set_title(String title);
    };
} // pax

#endif // PAX_ENGINE_DISPLAY_HPP
