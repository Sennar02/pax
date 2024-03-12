#ifndef GAME_ACTOR_LAYER_HPP
#define GAME_ACTOR_LAYER_HPP

#include <pax/Engine/import.hpp>
#include "Piece.hpp"

namespace game
{
    using namespace pax;

    struct Actor_Layer_Draw
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

        /**
         *
         */
        Array<Location>* lctns = 0;

    public:
        /**
         *
         */
        void
        after_step(Array2d<u64>& table);
    };

    struct Actor_Layer_Write
        : public Grid_Step
    {
    public:
        /**
         *
         */
        u64 frame = 0;

        /**
         *
         */
        u64 limit = 0;

        /**
         *
         */
        View* view = 0;

    public:
        /**
         *
         */
        void
        fixed_step(f64 time, Array2d<u64>& table);
    };

    struct Actor_Layer_Control
        : public Grid_Step
    {
    public:
        /**
         *
         */
        Array<Movement>* mvmts = 0;

        /**
         *
         */
        Array<Controls*>* ctrls = 0;

    public:
        /**
         *
         */
        void
        fixed_step(f64 time, Array2d<u64>& table);
    };

    struct Actor_Layer_Collide
        : public Grid_Step
    {
    public:
        /**
         *
         */
        Array<Location>* lctns = 0;

        /**
         *
         */
        Array<Movement>* mvmts = 0;

    public:
        /**
         *
         */
        void
        fixed_step(f64 time, Array2d<u64>& table);
    };

    struct Actor_Layer_Move
        : public Grid_Step
    {
    public:
        /**
         *
         */
        Array<Location>* lctns = 0;

        /**
         *
         */
        Array<Movement>* mvmts = 0;

        /**
         *
         */
        View* view = 0;

    public:
        /**
         *
         */
        void
        fixed_step(f64 time, Array2d<u64>& table);

    private:
        /**
         *
         */
        void
        begin_movement(u64 actor, Location* lctn, Movement* mvmt, Array2d<u64>& table);

        /**
         *
         */
        void
        compl_movement(u64 actor, Location* lctn, Movement* mvmt, f64 time);
    };
} // game

#endif // GAME_ACTOR_LAYER_HPP
