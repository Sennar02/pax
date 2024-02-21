#ifndef LIGHT_ENGINE_ACTOR_HPP
#define LIGHT_ENGINE_ACTOR_HPP

#include <light/Engine/define.hpp>

namespace light
{
    struct Actor
    {
    public:
        /**
         * Unique identifier of the actor.
         */
        u32 ident;

        /**
         * Bit mask of part identifiers to determine
         * of which parts the actor is made up of.
         */
        u32 parts;

    public:
        /**
         * Sets the bit corresponding to a part.
         */
        void
        attach_part(u32 part);

        /**
         * Clears the bit corresponding to a part.
         */
        void
        detach_part(u32 part);
    };
} // light

#endif // LIGHT_ENGINE_ACTOR_HPP
