#ifndef DEMO_MOVEMENT_HPP
#define DEMO_MOVEMENT_HPP

#include "define.hpp"

struct Movement
{
public:
    /**
     *
     */
    static const u64 FLAGS_MOBILE = 1u;

    /**
     *
     */
    static const u64 FLAGS_MOVING = 2u;

public:
    /**
     * Point where the movement should bring to, in world coordinates.
     */
    v2u64 target = {};

    /**
     * Movement direction in grid coordinates.
     */
    v2s64 angle = {};

    /**
     * todo: Comment.
     */
    v2s64 input = {};

    /**
     * Movement speed.
     */
    f64 speed = 0;

    /**
     * Movement speed limit.
     */
    f64 limit = 0;

    /**
     *  Additional flags.
     */
    u64 flags = 0;

public:
    /**
     * Determines if the actor is mobile.
     */
    bool
    is_mobile() const;

    /**
     * Determines if the actor is currently moving.
     */
    bool
    is_moving() const;

    /**
     * todo: Comment.
     */
    void
    set_mobile(bool state);

    /**
     * todo: Comment.
     */
    void
    set_moving(bool state);
};

bool
Movement::is_mobile() const
{
    return bits_test(flags, Movement::FLAGS_MOBILE);
}

bool
Movement::is_moving() const
{
    return bits_test(flags, Movement::FLAGS_MOVING);
}

void
Movement::set_mobile(bool state)
{
    flags = bits_copy(flags, Movement::FLAGS_MOBILE, state);
}

void
Movement::set_moving(bool state)
{
    flags = bits_copy(flags, Movement::FLAGS_MOVING, state);
}

#endif // DEMO_MOVEMENT_HPP