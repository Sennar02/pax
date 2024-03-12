#ifndef GAME_CONTROLS_HPP
#define GAME_CONTROLS_HPP

#include <pax/Engine/import.hpp>
#include "Piece.hpp"

namespace game
{
    using namespace pax;

    struct Player_Controls
        : public Controls
    {
    public:
        /**
         *
         */
        Array<const s8>* keys = 0;

    public:
        /**
         *
         */
        v2s64
        movement_step();
    };

    struct Random_Controls
        : public Controls
    {
    public:
        /**
         *
         */
        u64 spaces = 0;

        /**
         *
         */
        v2s64 cached = {};

    public:
        /**
         *
         */
        v2s64
        movement_step();
    };
} // game

#endif // GAME_CONTROLS_HPP
