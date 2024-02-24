#ifndef LIGHT_ENGINE_DISPLAY_HPP
#define LIGHT_ENGINE_DISPLAY_HPP

#include <light/Engine/define.hpp>

namespace light
{
    struct Display
    {
    public:
        /**
         * Internal pointer.
         */
        SDL_Window* data;

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
        create(String title, Vec2u size, u32 flags = 0);

        /**
         *
         */
        void
        destroy();
    };
} // light

#endif // LIGHT_ENGINE_DISPLAY_HPP
