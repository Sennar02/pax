#ifndef PAX_ENGINE_STATE_HPP
#define PAX_ENGINE_STATE_HPP

#include <pax/Engine/define.hpp>

namespace pax
{
    struct State
    {
    public:
        /**
         * todo: Comment.
         */
        String next;

    public:
        /**
         * todo: Comment.
         */
        virtual void
        acquire();

        /**
         * todo: Comment.
         */
        virtual void
        release();

        /**
         * todo: Comment.
         */
        virtual void
        enter();

        /**
         * todo: Comment.
         */
        virtual void
        leave();

        /**
         * todo: Comment.
         */
        virtual bool
        input();

        /**
         * todo: Comment.
         */
        virtual void
        fixed_step(f64 step);

        /**
         * todo: Comment.
         */
        virtual void
        after_step();
    };
} // pax

#endif // PAX_ENGINE_STATE_HPP
