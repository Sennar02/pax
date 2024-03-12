#include "Actor_Layer.hpp"

namespace game
{
    void
    Actor_Layer_Draw::after_step(Array2d<u64>& table)
    {
        v4f64     bounds = view->bounds();
        v4u64     culled = view->cull(bounds, {0, 0, table.cols, table.rows});
        v4u64     rgba   = {};
        v4f64     tile   = {};
        u64       actor  = 0;
        Location* lctn  = 0;

        tile[2] = tile[3] = view->unit;

        for ( u64 r = culled[1]; r < culled[3]; r += 1u ) {
            for ( u64 c = culled[0]; c < culled[2]; c += 1u ) {
                actor = table[{c, r}];

                if ( actor != 0 ) {
                    lctn = &(*lctns)[actor - 1u];
                    rgba = (*colrs)[actor - 1u];

                    tile[0] = lctn->point[0] - bounds[0];
                    tile[1] = lctn->point[1] - bounds[1];

                    painter->set_colour(rgba);
                    painter->fill_rect(tile);
                }
            }
        }

        painter->set_colour();
    }

    void
    Actor_Layer_Write::fixed_step(f64, Array2d<u64>& table)
    {
        v4f64    bounds = view->bounds();
        v4u64    culled = view->cull(bounds, {0, 0, table.cols, table.rows});
        u64      index  = 0;

        frame += 1u;

        if ( frame == limit ) frame = 0;
        if ( frame != 0 ) return;

        system("clear");

        for ( u64 r = 0; r < table.rows; r += 1u ) {
            for ( u64 c = 0; c < table.cols; c += 1u ) {
                index = table[{c, r}];

                if ( c >= culled[0] && c < culled[2] &&
                     r >= culled[1] && r < culled[3] )
                    printf("\x1b[46m");

                if ( index != 0 ) {
                    if ( index != 1u )
                        printf("\x1b[93m%3lu\x1b[0m ", index);
                    else
                        printf("\x1b[91m%3lu\x1b[0m ", index);
                } else
                    printf("\x1b[90m ~ \x1b[0m ");
            }

            printf("\n");
        }

        printf("(%lu, %lu) --> (%lu, %lu) [%lf]\n",
            culled[0], culled[1],
            culled[2], culled[3],
            view->factor
        );
    }

    void
    Actor_Layer_Control::fixed_step(f64, Array2d<u64>&)
    {
        u64       size = pax_min(mvmts->size, ctrls->size);
        Movement* mvmt = 0;
        Controls* ctrl = 0;

        for ( u64 i = 0; i < size; i += 1u ) {
            mvmt = &(*mvmts)[i];
            ctrl = (*ctrls)[i];

            if ( bits_test(mvmt->flag, Movement::MOBILE) ) {
                if ( mvmt != 0 && ctrl != 0 )
                    mvmt->step_input = ctrl->movement_step();
            } else
                pax_panic("null", "mvmt[%lu] = %p, ctrl[%lu] = %p",
                    i, (void*) mvmt, i, (void*) ctrl
                );
        }
    }

    void
    Actor_Layer_Collide::fixed_step(f64, Array2d<u64>& table)
    {
        static const Buf<v2u64, 3u> dirs = {
            v2u64 {1u, 0},
            v2u64 {0, 1u},
            v2u64 {1u, 1u}
        };

        v2u64     bounds = {table.cols, table.rows};
        v2u64     tile   = {};
        v2u64     next   = {};
        v2s64     comp   = {};
        Movement* mvmt   = 0;
        Location* lctn   = 0;

        for ( u64 i = 0; i < mvmts->size; i += 1u ) {
            mvmt = &(*mvmts)[i];
            lctn = &(*lctns)[i];

            tile.from(lctn->point / mvmt->step_unit);
            next = tile + mvmt->step_input;

            for ( u64 d = 0; d < bounds.SIZE; d += 1u )
                if ( next[d] >= bounds[d] ) mvmt->step_input[d] = 0;

            for ( u64 d = 0; d < dirs.SIZE; d += 1u ) {
                comp = mvmt->step_input * dirs[d];
                next = tile + comp;

                if ( table[next] != 0 )
                    mvmt->step_input -= comp;
            }
        }
    }

    void
    Actor_Layer_Move::fixed_step(f64 time, Array2d<u64>& table)
    {
        u64       size = pax_min(lctns->size, mvmts->size);
        Location* lctn = 0;
        Movement* mvmt = 0;

        for ( u64 i = 0; i < size; i += 1u ) {
            lctn = &(*lctns)[i];
            mvmt = &(*mvmts)[i];

            if ( bits_read(mvmt->flag, Movement::MOBILE) &&
                 bits_read(mvmt->flag, Movement::MOVING) == false ) {
                if ( mvmt->step_input != v2s64 {} )
                    begin_movement(i + 1u, lctn, mvmt, table);
            }

            if ( bits_test(mvmt->flag, Movement::MOVING) )
                compl_movement(i + 1u, lctn, mvmt, time);
        }

        view->centre = (*lctns)[0].point;
    }

    void
    Actor_Layer_Move::begin_movement(u64 actor, Location* lctn, Movement* mvmt, Array2d<u64>& table)
    {
        v2u64 origin = {};
        v2u64 finish = {};

        origin.from(lctn->point / mvmt->step_unit);
        finish = origin + mvmt->step_input;

        if ( table[finish] == 0 ) {
            mvmt->step_limit  = lctn->point + mvmt->step_input * mvmt->step_unit;
            mvmt->step_value  = mvmt->step_input;
            mvmt->speed_value = mvmt->speed_limit / mvmt->step_value.magnitude();
            mvmt->flag =
                bits_write(mvmt->flag, Movement::MOVING, 1);

            table[origin] = 0;
            table[finish] = actor;
        }
    }

    void
    Actor_Layer_Move::compl_movement(u64, Location* lctn, Movement* mvmt, f64 time)
    {
        f64 incr = 0;
        f64 dist = 0;

        for ( u64 d = 0; d < mvmt->step_value.SIZE; d += 1u ) {
            incr = mvmt->step_value[d] * mvmt->speed_value * time;
            dist = abs(mvmt->step_limit[d] - lctn->point[d]);

            lctn->point[d] += incr;

            if ( dist < abs(incr) )
                lctn->point[d] = mvmt->step_limit[d];
        }

        if ( lctn->point == mvmt->step_limit )
            mvmt->flag = bits_write(mvmt->flag, Movement::MOVING, 0);
    }
} // game
