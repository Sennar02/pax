#include "Controls.hpp"

namespace game
{
    v2s64
    Player_Controls::movement_step()
    {
        static const u64 NORTH = SDL_SCANCODE_W;
        static const u64 EAST  = SDL_SCANCODE_D;
        static const u64 SOUTH = SDL_SCANCODE_S;
        static const u64 WEST  = SDL_SCANCODE_A;

        return {
            (*keys)[EAST]  - (*keys)[WEST],
            (*keys)[SOUTH] - (*keys)[NORTH],
        };
    }

    v2s64
    Random_Controls::movement_step()
    {
        if ( rand() % (spaces + 1u) == 0 )
            cached = {rand() % 3 - 1, rand() % 3 - 1};

        return cached;
    }
} // game
