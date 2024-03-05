#include <light/Signal/import.hpp>

#include <time.h>  // time
#include <stdio.h> // printf

#include "game/Piece.hpp"
#include "game/Game_State.hpp"
#include "game/Floor_Layer.hpp"
#include "game/Actor_Layer.hpp"
#include "game/Controls.hpp"

using namespace game;

static const u64   TILE_SIZE    = 48u;        // Pixels.
static const v2u64 GRID_SIZE    = {160u, 90u}; // Tiles.
static const v2u64 VIEW_SIZE    = { 16u,  9u};  // Tiles.

static const u64 GRID_LAYERS = 10u;
static const u64 GRID_STEPS  = 10u;

static const u64 ACTORS_COUNT = 500u;

static const Buf<v4u64, 4u> FLOOR_COLOURS = {
    v4u64 {0x32, 0x70, 0x00, 0xff},
    v4u64 {0x00, 0x70, 0x05, 0xff},
    v4u64 {0x6a, 0x70, 0x00, 0xff},
    v4u64 {0x6b, 0x34, 0x01, 0xff}
};

static const u64        bump_size = 1024u * 256u;
static       Bump_Alloc bump      = Bump_Alloc();

int
main(int, const char*[])
{
    bump = Bump_Alloc(calloc(1u, bump_size), bump_size);

    Array<v4u64>     colrs = Array<v4u64>(ACTORS_COUNT, &bump);
    Array<Location>  lctns = Array<Location>(ACTORS_COUNT, &bump);
    Array<Movement>  mvmts = Array<Movement>(ACTORS_COUNT, &bump);
    Array<Controls*> ctrls = Array<Controls*>(ACTORS_COUNT, &bump);

    Array<v4u64> floor = Array<v4u64>(
        (void*) FLOOR_COLOURS.data, FLOOR_COLOURS.SIZE
    );

    Engine     engine;
    Game_State game_state = Game_State(
        GRID_SIZE,
        GRID_LAYERS,
        GRID_STEPS,
        TILE_SIZE,
        VIEW_SIZE
    );

    u64 frames = 256u;

    Floor_Layer_Draw    floor_draw;
    Actor_Layer_Draw    actor_draw;
    Actor_Layer_Write   actor_write;
    Actor_Layer_Control actor_control;
    Actor_Layer_Collide actor_collide;
    Actor_Layer_Move    actor_move;

    floor_draw.painter = &game_state.painter;
    floor_draw.view    = &game_state.view;
    floor_draw.colrs   = &floor;

    actor_draw.painter = &game_state.painter;
    actor_draw.view    = &game_state.view;
    actor_draw.colrs   = &colrs;
    actor_draw.lctns   = &lctns;

    actor_write.view  = &game_state.view;
    actor_write.limit = frames / 4u;

    actor_control.mvmts = &mvmts;
    actor_control.ctrls = &ctrls;

    actor_collide.lctns = &lctns;
    actor_collide.mvmts = &mvmts;

    actor_move.lctns = &lctns;
    actor_move.mvmts = &mvmts;
    actor_move.view  = &game_state.view;

    srand( time(0) );

    game_state.grid.layers[0].table.fill([](Array<v4u64>& floor) {
        return rand() % floor.size;
    }, floor);

    mvmts.fill([]() {
        Movement mvmt;

        mvmt.step_unit   = TILE_SIZE;
        mvmt.speed_limit = rand() % 15 * TILE_SIZE;
        mvmt.flag =
            bits_write(mvmt.flag, Movement::MOBILE, mvmt.speed_limit != 0);

        return mvmt;
    });

    for ( u64 i = 0; i < ACTORS_COUNT; i += 1u ) {
        v2u64 point = {};

        do {
            point = {
                rand() % game_state.grid.layers[1].table.cols,
                rand() % game_state.grid.layers[1].table.rows,
            };
        } while ( game_state.grid.layers[1].table[point] != 0 );

        game_state.grid.layers[1].table[point] = i + 1u;

        if ( i != 0 ) {
            ctrls[i] = reserve<Random_Controls>(bump);

            if ( ctrls[i] != 0 )
                ((Random_Controls*) ctrls[i])->spaces = rand() % frames;
            else
                light_panic("null", "ctrls[i] == %p", (void*) ctrls[i]);
        } else {
            const u8* keys = 0;
            s32       size = 0;

            keys = SDL_GetKeyboardState(&size);

            ctrls[i] = reserve<Player_Controls>(bump);
            ((Player_Controls*) ctrls[i])->keys = reserve<Array<const s8>>(bump);
            ((Player_Controls*) ctrls[i])->keys->data = (const s8*) keys;
            ((Player_Controls*) ctrls[i])->keys->size = size;
        }

        lctns[i].point.from(point * TILE_SIZE);
        colrs[i] = {
            (u8) rand() % 0x40u + 0xa0u,
            (u8) rand() % 0x40u + 0xa0u,
            (u8) rand() % 0x40u + 0xa0u,
            (u8) rand() % 0x40u + 0xa0u,
        };
    }

    game_state.view.centre = lctns[0].point;
    game_state.view.offset = {TILE_SIZE / 2u, TILE_SIZE / 2u};

    colrs[0] = {0xffu, 0xffu, 0xffu, 0xffu};
    mvmts[0].speed_limit = 10 * TILE_SIZE;

    game_state.grid.layers[0].push(&floor_draw);
    game_state.grid.layers[1].push(&actor_draw);

    #define LIGHT_ACTOR_WRITE false

    #if LIGHT_ACTOR_WRITE
        game_state.grid.layers[1].push(&actor_write);
    #endif

    game_state.grid.layers[1].push(&actor_control);
    game_state.grid.layers[1].push(&actor_collide);
    game_state.grid.layers[1].push(&actor_move);

    if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        printf("%s\n", SDL_GetError());

        return -1;
    }

    engine.execute(game_state, frames);

    SDL_Quit();

    free(bump.data);

    return 0;
}

