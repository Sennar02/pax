#ifndef GAME_FLOOR_LAYER_HPP
#define GAME_FLOOR_LAYER_HPP

#include <light/Engine/import.hpp>

namespace game
{
    using namespace light;

    struct Floor_Layer_Draw
        : public Grid_Step
    {
    public:
        /**
         *
         */
        Painter* painter = 0;

        /**
         *
         */
        View* view = 0;

        /**
         *
         */
        Array<v4u64>* colrs = 0;

    public:
        /**
         *
         */
        void
        after_step(Array2d<u64>& table);
    };
} // game

#endif // GAME_FLOOR_LAYER_HPP
