#ifndef PAX_ENGINE_ENGINE_HPP
#define PAX_ENGINE_ENGINE_HPP

#include <pax/Engine/define.hpp>
#include <pax/Engine/Clock.hpp>
#include <pax/Engine/State.hpp>

namespace pax
{
    struct Engine
    {
    public:
        /**
         * todo: Comment.
         */
        Clock clock;

    public:
        /**
         * todo: Comment.
         */
        bool
        loop(State& state, f64 frame_rate);

        /**
         * todo: Comment.
         */
        bool
        startup();

        /**
         * todo: Comment.
         */
        bool
        cleanup();
    };
} // pax


#endif // PAX_ENGINE_ENGINE_HPP
