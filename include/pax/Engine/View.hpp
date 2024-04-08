#ifndef PAX_ENGINE_VIEW_HPP
#define PAX_ENGINE_VIEW_HPP

#include <pax/Engine/define.hpp>

namespace pax
{
    struct View
    {
    public:
        /**
         * todo: Comment.
         */
        v2f64 target = {};

        /**
         * todo: Comment.
         */
        v2f64 offset = {};

        /**
         * todo: Comment.
         */
        v2f64 size = {};

        /**
         * todo: Comment.
         */
        v2f64 unit = {};

        /**
         * todo: Comment.
         */
        v2f64 scale = {1.0, 1.0};

    public:
        /**
         * todo: Comment.
         */
        v4f64
        rect() const;

        /**
         * todo: Comment.
         */
        v4u64
        cull(v4f64 bounds, v4u64 limits) const;

        /**
         * todo: Comment.
         */
        v4s64
        snap(v4f64 bounds) const;
    };
} // pax


#endif // PAX_ENGINE_VIEW_HPP
