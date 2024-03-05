#include "Floor_Layer.hpp"

namespace game
{
    void
    Floor_Layer_Draw::after_step(Array2d<u64>& table)
    {
        v4f64 bounds = view->bounds();
        v4u64 culled = view->cull(bounds, {0, 0, table.cols, table.rows});
        v4u64 rgba   = {};
        v4f64 tile   = {};

        tile[2] = tile[3] = view->unit;

        for ( u64 r = culled[1]; r < culled[3]; r += 1u ) {
            for ( u64 c = culled[0]; c < culled[2]; c += 1u ) {
                rgba = (*colrs)[table[{c, r}]];

                tile[0] = tile[2] * c - bounds[0];
                tile[1] = tile[3] * r - bounds[1];

                painter->set_colour(rgba);
                painter->fill_rect(tile);
            }
        }

        painter->set_colour();
    }
} // game
