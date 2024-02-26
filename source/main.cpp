#include <light/Engine/import.hpp>

#include <time.h>  // time
#include <stdio.h> // printf

#include "game/Piece.hpp"

using namespace game;

struct Grid_Layer
{
public:
    Array2d<u64> grid;

public:
    virtual void
    draw(const View& view, Painter& painter) const = 0;
};

struct Floor_Layer
    : public Grid_Layer
{
public:
    virtual void
    draw(const View& view, Painter& painter) const;
};

struct Actor_Layer
    : public Grid_Layer
{
public:
    virtual void
    draw(const View& view, Painter& painter) const;
};

static const u64   TILE_SIZE    = 12u;        // Pixels.
static const Vec2u GRID_SIZE    = {45u, 25u}; // Tiles.
static const Vec2u VIEW_SIZE    = {50u, 50u};  // Tiles.
static const Vec2u DISPLAY_SIZE = {50u, 50u};  // Tiles.

static const u64   TILE_HALF    = TILE_SIZE / 2u;
static const Vec2u GRID_HALF    = GRID_SIZE / 2u;
static const Vec2u VIEW_HALF    = VIEW_SIZE / 2u;
static const Vec2u DISPLAY_HALF = DISPLAY_SIZE / 2u;

static const u64 GRID_AREA =
    GRID_SIZE[0] * GRID_SIZE[1];

static const u64 ACTOR_COUNT = 200u;

// TODO: Implement a tile system.
static const u64 COLOURS_COUNT = 4u;

// TODO: Implement a tile system.
static const Vec4u COLOURS_FLOOR[COLOURS_COUNT] = {
    {0x32, 0x70, 0x00, 0xff},
    {0x00, 0x70, 0x05, 0xff},
    {0x6a, 0x70, 0x00, 0xff},
    {0x6b, 0x34, 0x01, 0xff},
};

// TODO: Implement an input system.
static const u8* KEYBOARD = 0;

static Array<Vec4u>    COLOUR   = Array<Vec4u>(ACTOR_COUNT);
static Array<Position> POSITION = Array<Position>(ACTOR_COUNT);
static Array<Motion>   MOTION   = Array<Motion>(ACTOR_COUNT);
static Array<Controls> CONTROLS = Array<Controls>(ACTOR_COUNT);

Vec2f
motion_func_player(void*)
{
    static const u64 DIR_NORTH = SDL_SCANCODE_W;
    static const u64 DIR_EAST  = SDL_SCANCODE_D;
    static const u64 DIR_SOUTH = SDL_SCANCODE_S;
    static const u64 DIR_WEST  = SDL_SCANCODE_A;

    return {
        (f64) KEYBOARD[DIR_EAST]  - KEYBOARD[DIR_WEST],
        (f64) KEYBOARD[DIR_SOUTH] - KEYBOARD[DIR_NORTH],
    };
}

Vec2f
motion_func_random(void*)
{
    if ( rand() % 10u == 0 )
        return {rand() % 3 - 1.0, rand() % 3 - 1.0};

    return {};
}

void
Floor_Layer::draw(const View& view, Painter& painter) const
{
    Vec2f origin = view.origin();
    Vec4u limits = view.visible(GRID_SIZE);
    Vec4f tile   = {};
    Vec4u rgba   = {};
    u64   index  = 0;

    tile[2] = tile[3] = view.unit;

    for ( u64 j = limits[2]; j < limits[3]; j += 1u ) {
        for ( u64 i = limits[0]; i < limits[1]; i += 1u ) {
            index = grid[{i, j}];
            rgba  = COLOURS_FLOOR[index];

            tile[0] = i * view.unit - origin[0];
            tile[1] = j * view.unit - origin[1];

            painter.set_colour(rgba);
            painter.draw_rect_full(tile);
        }
    }

    painter.set_colour({});
}

void
Actor_Layer::draw(const View& view, Painter& painter) const
{
    Vec2f origin = view.origin();
    Vec4u limits = view.visible(GRID_SIZE);
    Vec4f tile   = {};
    Vec4u rgba   = {};
    u64   index  = 0;
    u64   actor  = 0;

    tile[2] = tile[3] = view.unit;

    for ( u64 j = limits[2]; j < limits[3]; j += 1u ) {
        for ( u64 i = limits[0]; i < limits[1]; i += 1u ) {
            index = grid[{i, j}];
            actor = index - 1u;

            if ( index != 0 ) {
                rgba = COLOUR[actor];

                tile[0] = POSITION[actor][0] - origin[0];
                tile[1] = POSITION[actor][1] - origin[1];

                painter.set_colour(rgba);
                painter.draw_rect_full(tile);
            }
        }
    }

    painter.set_colour({});
}

void
control()
{
    for ( u64 i = 0; i < ACTOR_COUNT; i += 1u ) {
        Motion&   mot = MOTION[i];
        Controls& ctl = CONTROLS[i];

        if ( bit_test(mot.status, Motion::MOBILE) )
            mot.step_input = ctl.motion(0);
    }
}

void
collide(Grid_Layer& layer)
{
    static const u64   DIRS_COUNT       = 3u;
    static const Vec2u DIRS[DIRS_COUNT] = {{1u, 0}, {0, 1u}, {1u, 1u}};

    Vec2u next = {};
    Vec2u tile = {};
    Vec2f part = {};

    for ( u64 j = 0; j < ACTOR_COUNT; j += 1u ) {
        Motion& mot = MOTION[j];

        tile = mot.tile_origin;
        next = tile + mot.step_input;

        if ( next[0] >= GRID_SIZE[0] ) mot.step_input[0] = 0;
        if ( next[1] >= GRID_SIZE[1] ) mot.step_input[1] = 0;

        if ( mot.step_input[0] == 0 && mot.step_input[1] == 0 ) continue;

        for ( u64 i = 0; i < DIRS_COUNT; i += 1u ) {
            part = mot.step_input * DIRS[i];
            next = tile + part;

            if ( layer.grid[next] != 0 )
                mot.step_input -= part;
        }
    }
}


void
move(Grid_Layer& layer, f64 time)
{
    f64   dist = 0;
    f64   incr = 0;
    Vec2f stop = {};

    for ( u64 j = 0; j < ACTOR_COUNT; j += 1u ) {
        Motion&   mot = MOTION[j];
        Position& pos = POSITION[j];

        if ( bit_test(mot.status, Motion::MOBILE) &&
             bit_test(mot.status, Motion::MOVING) == false ) {
            if ( mot.step_input != Vec2f {} ) {
                mot.tile_origin.from(pos / TILE_SIZE);

                mot.step_value  = mot.step_input;
                mot.speed_value = mot.speed_limit / mot.step_value.magnitude();
                mot.tile_finish = mot.tile_origin + mot.step_value;

                if ( layer.grid[mot.tile_finish] == 0 ) {
                    mot.status = bit_write(mot.status, Motion::MOVING, 1);

                    layer.grid[mot.tile_finish] = j + 1u;
                    layer.grid[mot.tile_origin] = 0;
                }
            }
        }

        if ( bit_test(mot.status, Motion::MOVING) ) {
            stop.from(mot.tile_finish * TILE_SIZE);

            for ( u64 i = 0; i < mot.step_value.SIZE; i += 1u ) {
                incr = mot.step_value[i] * mot.speed_value * time;
                dist = abs(stop[i] - pos[i]);

                pos[i] += incr;

                if ( dist < abs(incr) )
                    pos[i] = stop[i];
            }

            if ( pos == stop ) {
                mot.status      = bit_write(mot.status, Motion::MOVING, 0);
                mot.tile_origin = mot.tile_finish;
            }
        }
    }
}

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
    u64         player;
    View        view;
    Display     display;
    Painter     painter;
    Floor_Layer floor_layer;
    Actor_Layer actor_layer;
};

Title_State::Title_State()
    : player {0}
    , view {}
    , display {}
    , painter {}
    , floor_layer {}
    , actor_layer {}
{
    floor_layer.grid = Array2d<u64>(GRID_SIZE);
    actor_layer.grid = Array2d<u64>(GRID_SIZE);
}

void
Title_State::startup()
{
    String title = String("Light", 0, 5u);
    u64    actor = 0;
    Vec2u  pos;

    for ( u64 i = 0; i < GRID_AREA; i += 1u )
        floor_layer.grid[i] = rand() % COLOURS_COUNT;

    for ( u64 i = 0; i < ACTOR_COUNT; i += 1u ) {
        do {
            pos = {
                rand() % GRID_SIZE[0],
                rand() % GRID_SIZE[1],
            };

            actor = actor_layer.grid[pos];
        } while ( actor != 0 );

        CONTROLS[i].motion    = &motion_func_random;
        MOTION[i].tile_origin = pos;
        MOTION[i].speed_limit = 15.0 * TILE_SIZE;
        MOTION[i].status      = bit_write(MOTION[i].status, Motion::MOBILE, 1);
        COLOUR[i]             = {
            ((u8) rand() % 0x40) + 0xa0u,
            ((u8) rand() % 0x40) + 0xa0u,
            ((u8) rand() % 0x40) + 0xa0u,
            0xff,
        };

        POSITION[i].from(pos * TILE_SIZE);

        actor_layer.grid[pos] = i + 1u;
    }

    COLOUR[player]          = {0xff, 0xff, 0xff, 0xff};
    CONTROLS[player].motion = &motion_func_player;

    view.centre = POSITION[player] + TILE_HALF;
    view.unit   = TILE_SIZE;
    view.size   = VIEW_SIZE;

    display.create(title, DISPLAY_SIZE * TILE_SIZE);

    if ( display.is_valid() ) {
        painter.create(display);

        if ( painter.is_valid() == false )
            display.destroy();
    }
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
    SDL_Event event;

    while ( SDL_PollEvent(&event) ) {
        if ( event.type == SDL_QUIT ) return false;

        if ( event.type == SDL_KEYUP ) {
            if ( event.key.keysym.sym == SDLK_ESCAPE )
                return false;
        }
    }

    return true;
}

void
Title_State::fixed_step(f64 time)
{
    SDL_PumpEvents();

    control();
    collide(actor_layer);

    move(actor_layer, time);

    view.centre = POSITION[player] + TILE_HALF;

#define PRINT_WORLD 0

#if PRINT_WORLD
    u64   index  = 0;
    Vec4u limits = view.visible(GRID_SIZE);

    system("clear");

    for ( u64 j = 0; j < GRID_SIZE[1]; j += 1u ) {
        for ( u64 i = 0; i < GRID_SIZE[0]; i += 1u ) {
            index = actor_layer.grid[{i, j}];

            if ( i >= limits[0] && i < limits[1] &&
                 j >= limits[2] && j < limits[3])
                printf("\x1b[46m");

            if ( index != 0 )
                printf("\x1b[93m%3lu\x1b[0m ", index);
            else
                printf("\x1b[90m ~ \x1b[0m ");
        }

        printf("\n");
    }

    printf("[%lu, %lu) x [%lu, %lu)\n",
        limits[0], limits[1],
        limits[2], limits[3]
    );
#endif
}

void
Title_State::after_step()
{
    painter.swap();

    floor_layer.draw(view, painter);
    actor_layer.draw(view, painter);

    painter.show();
}

int
main(int, const char*[])
{
    Title_State title_state;
    Engine      engine;

    srand( time(0) );

    if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        printf("%s\n", SDL_GetError());

        return -1;
    }

    KEYBOARD = SDL_GetKeyboardState(0);
    engine.execute(&title_state, 144u);

    SDL_Quit();

    return 0;
}
