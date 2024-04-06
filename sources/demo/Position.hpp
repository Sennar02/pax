#ifndef DEMO_POSITION_HPP
#define DEMO_POSITION_HPP

#include "define.hpp"

struct Position
{
public:
    /**
     * Coordinates of the actor in tiles.
     */
    v2u64 point = {};

    /**
     * Displacement from the point in which the actor lies.
     */
    v2f64 displ = {};

public:
    /**
     * todo: Comment.
     */
    v2f64
    whole() const;
};

v2f64
Position::whole() const
{
    return displ + point;
}

#endif // DEMO_POSITION_HPP