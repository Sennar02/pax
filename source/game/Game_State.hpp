#ifndef GAME_GAME_STATE_HPP
#define GAME_GAME_STATE_HPP

#include <pax/Engine/define.hpp>
#include <pax/Signal/import.hpp>
#include "Piece.hpp"

namespace game
{
    using namespace pax;

    struct Game_State
        : public State
    {
    public:
        /**
         *
         */
        Game_State(
            v2u64 grid_size,
            u64   grid_layers,
            u64   grid_steps,
            u64   tile_size,
            v2u64 view_size
        );

        /**
         *
         */
        void
        startup();

        /**
         *
         */
        void
        cleanup();

        /**
         *
         */
        void
        enter();

        /**
         *
         */
        void
        leave();

        /**
         *
         */
        bool
        input();

        /**
         *
         */
        void
        fixed_step(f64 time, u64 tick);

        /**
         *
         */
        void
        after_step();

    public:
        /**
         *
         */
        Display display;

        /**
         *
         */
        Painter painter;

        /**
         *
         */
        Grid grid;

        /**
         *
         */
        View view;

        f64   mult = 0.01;
        v2u64 grid_size;
        u64   tile_size;
        v2u64 view_size;
    };
} // game
/*
struct Title_State
    : public State
{
public:
    Title_State();

    void
    startup();

    void
    cleanup();

    void
    enter();

    void
    leave();

    bool
    input();

    void
    fixed_step(f64 time);

    void
    after_step();

public:
    u64     player;
    View    view;
    Grid    grid;
    Display display;
    Painter painter;
    Floor_Draw floor_draw;
    Actor_Draw actor_draw;
    Actor_Write actor_write;
    Player_Controls player_controls;
    Random_Controls random_controls;
};

Title_State::Title_State()
    : player {0}
    , view {}
    , grid {}
    , display {}
    , painter {}
    , floor_draw {}
    , actor_draw {}
    , actor_write {}
    , player_controls {}
    , random_controls {}
{
    Grid_Layer layer;

    grid.layers = Array<Grid_Layer>(GRID_LAYERS_COUNT, &memory);

    for ( u64 i = 0; i < grid.layers.size; i += 1u ) {
        layer.table = Array2d<u64>(GRID_SIZE, &memory);
        layer.steps = Array<Grid_Step*>(GRID_STEPS_COUNT, &memory);

        grid.push(layer);
    }

    floor_draw.painter = &painter;
    floor_draw.view    = &view;

    actor_draw.painter = &painter;
    actor_draw.view    = &view;

    actor_write.view = &view;

    grid.layers[0].push(&floor_draw);
    grid.layers[1].push(&actor_draw);

    #define PAX_WRITE_ACTORS false

    #if PAX_WRITE_ACTORS
        grid.layers[1].push(&actor_write);
    #endif

    player_controls.keyboard = &KEYBOARD;
}

void
Title_State::startup()
{
    String title = String("Light", 0, 5u);
    u64    actor = 0;
    v2u64  point;

    for ( u64 i = 0; i < GRID_AREA; i += 1u )
        grid.layers[0].table[i] = rand() % COLOURS_COUNT;

    for ( u64 i = 0; i < ACTORS_COUNT; i += 1u ) {
        do {
            point = {
                rand() % grid.layers[1].table.cols,
                rand() % grid.layers[1].table.rows,
            };

            actor = grid.layers[1].table[point];
        } while ( actor != 0 );

        CONTROLS[i]           = &random_controls;
        MOTION[i].tile_origin = point;
        MOTION[i].speed_limit = rand() % 10 * TILE_SIZE;
        MOTION[i].flag        = bits_write(MOTION[i].flag, Motion::MOBILE, MOTION[i].speed_limit != 0);
        COLOUR[i]             = {
            ((u8) rand() % 0x40u) + 0xa0u,
            ((u8) rand() % 0x40u) + 0xa0u,
            ((u8) rand() % 0x40u) + 0xa0u,
            ((u8) rand() % 0x30u) + 0xc0u,
        };

        POSITION[i].from(point * TILE_SIZE);

        grid.layers[1].table[point] = i + 1u;
    }

    CONTROLS[player]           = &player_controls;
    MOTION[player].speed_limit = 10.0 * TILE_SIZE;
    MOTION[player].flag        = bits_write(MOTION[player].flag, Motion::MOBILE, 1);
    COLOUR[player]             = {0xff, 0xff, 0xff, 0xff};

    view.centre = POSITION[player] + TILE_HALF;
    view.unit   = TILE_SIZE;
    view.size   = VIEW_SIZE;

    display.create(title, DISPLAY_SIZE * TILE_SIZE);

    if ( display.is_valid() ) {
        painter.create(display);

        if ( painter.is_valid() == false )
            display.destroy();
    }

    painter.scale(1.0 / view.factor);
    painter.set_blend_mode(Painter::BLEND);
}

void
Title_State::cleanup()
{
    painter.destroy();
    display.destroy();
}

void
Title_State::enter()
{}

void
Title_State::leave()
{}

bool
Title_State::input()
{
    SDL_Signal event;

    while ( SDL_PollSignal(&event) ) {
        if ( event.type == SDL_QUIT ) return false;

        if ( event.type == SDL_KEYUP ) {
            if ( event.key.keysym.sym == SDLK_ESCAPE )
                return false;
        }

        if ( event.type == SDL_MOUSEWHEEL ) {
            view.factor = pax_max(
                view.factor + 0.01 * event.wheel.y, 0
            );
        }

        if ( event.type == SDL_MOUSEBUTTONDOWN ) {
            if ( event.button.button == SDL_BUTTON_MIDDLE )
                view.factor = 1;
        }

        painter.scale(view.factor);
    }

    return true;
}

void
Title_State::fixed_step(f64 time)
{
    Grid_Layer layer;

    SDL_PumpSignal();

    control();
    collide(grid.layers[1].table);
    move(time, grid.layers[1].table);

    for ( u64 j = 0; j < grid.count; j += 1u ) {
        layer = grid.layers[j];

        for ( u64 i = 0; i < layer.count; i += 1u )
            layer.steps[i]->fixed_step(time, layer.table);
    }

    view.centre = POSITION[player] + TILE_HALF;
}

void
Title_State::after_step()
{
    Grid_Layer layer;

    painter.swap();

    for ( u64 j = 0; j < grid.count; j += 1u ) {
        layer = grid.layers[j];

        for ( u64 i = 0; i < layer.count; i += 1u )
            layer.steps[i]->after_step(layer.table);
    }

    painter.show();
}
*/
#endif // GAME_GAME_STATE_HPP
