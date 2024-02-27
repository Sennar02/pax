#include <light/Engine/import.hpp>

#include <time.h>  // time
#include <stdio.h> // printf

#include "game/Piece.hpp"

using namespace game;

static const u64   TILE_SIZE    = 48u;        // Pixels.
static const Vec2u GRID_SIZE    = {45u, 25u}; // Tiles.
static const Vec2u VIEW_SIZE    = {16u, 9u};  // Tiles.
static const Vec2u DISPLAY_SIZE = {16u, 9u};  // Tiles.

static const u64   TILE_HALF    = TILE_SIZE / 2u;
static const Vec2u GRID_HALF    = GRID_SIZE / 2u;
static const Vec2u VIEW_HALF    = VIEW_SIZE / 2u;
static const Vec2u DISPLAY_HALF = DISPLAY_SIZE / 2u;

static const u64 GRID_AREA =
    GRID_SIZE[0] * GRID_SIZE[1];

static const u64 ACTORS_COUNT  = 200u;
static const u64 LAYERS_COUNT  = 2u;
static const u64 ACTIONS_COUNT = 1u;

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

static Array<Vec4u>    COLOUR   = Array<Vec4u>(ACTORS_COUNT);
static Array<Position> POSITION = Array<Position>(ACTORS_COUNT);
static Array<Motion>   MOTION   = Array<Motion>(ACTORS_COUNT);
static Array<Controls> CONTROLS = Array<Controls>(ACTORS_COUNT);

struct Draw_Context {
    Painter* painter = 0;
    View*    view    = 0;
};

void
floor_layer_draw(Array2d<u64>& indeces, void* extra)
{
    auto* context = (Draw_Context*) extra;

    if ( context == 0 ) return;

    Painter painter = *context->painter;
    View    view    = *context->view;
    Vec2f   offset  = view.offset();
    Vec4u   bounds  = view.visible({indeces.cols, indeces.rows});
    Vec4u   colour  = {};
    Vec4f   tile    = {};

    tile[2] = tile[3] = view.unit;

    for ( u64 j = bounds[2]; j < bounds[3]; j += 1u ) {
        for ( u64 i = bounds[0]; i < bounds[1]; i += 1u ) {
            colour = COLOURS_FLOOR[indeces[{i, j}]];

            tile[0] = tile[2] * i - offset[0];
            tile[1] = tile[3] * j - offset[1];

            painter.set_colour(colour);
            painter.fill_rect(tile);
        }
    }

    painter.set_colour();
}

void
actor_layer_draw(Array2d<u64>& indeces, void* extra)
{
    auto* context = (Draw_Context*) extra;

    if ( context == 0 ) return;

    Painter painter = *context->painter;
    View    view    = *context->view;
    Vec2f   offset  = view.offset();
    Vec4u   bounds  = view.visible({indeces.cols, indeces.rows});
    Vec4u   colour  = {};
    Vec4f   tile    = {};
    u64     actor   = 0;

    tile[2] = tile[3] = view.unit;

    for ( u64 j = bounds[2]; j < bounds[3]; j += 1u ) {
        for ( u64 i = bounds[0]; i < bounds[1]; i += 1u ) {
            actor = indeces[{i, j}];

            if ( actor != 0 ) {
                Position& pos = POSITION[actor - 1u];

                colour  = COLOUR[actor - 1u];
                tile[0] = pos[0] - offset[0];
                tile[1] = pos[1] - offset[1];

                painter.set_colour(colour);
                painter.fill_rect(tile);
            }
        }
    }

    painter.set_colour();
}

void
actor_layer_write(Array2d<u64>& indeces, void* extra)
{
    auto* context = (Draw_Context*) extra;

    if ( context == 0 ) return;

    View  view   = *context->view;
    Vec4u bounds = view.visible({indeces.cols, indeces.rows});
    u64   index  = 0;

    system("clear");

    for ( u64 j = 0; j < indeces.rows; j += 1u ) {
        for ( u64 i = 0; i < indeces.cols; i += 1u ) {
            index = indeces[{i, j}];

            if ( i >= bounds[0] && i < bounds[1] &&
                 j >= bounds[2] && j < bounds[3])
                printf("\x1b[46m");

            if ( index != 0 )
                printf("\x1b[93m%3lu\x1b[0m ", index);
            else
                printf("\x1b[90m ~ \x1b[0m ");
        }

        printf("\n");
    }

    printf("[%lu, %lu) x [%lu, %lu)\n",
        bounds[0], bounds[1],
        bounds[2], bounds[3]
    );
}

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
control()
{
    for ( u64 i = 0; i < ACTORS_COUNT; i += 1u ) {
        Motion&   mot = MOTION[i];
        Controls& ctl = CONTROLS[i];

        if ( bit_test(mot.status, Motion::MOBILE) )
            mot.step_input = ctl.motion(0);
    }
}

void
collide(Array2d<u64>& indeces)
{
    static const u64   DIRS_COUNT       = 3u;
    static const Vec2u DIRS[DIRS_COUNT] = {
        {1u, 0}, {0, 1u}, {1u, 1u},
    };

    Vec2u next = {};
    Vec2u tile = {};
    Vec2f part = {};

    for ( u64 j = 0; j < ACTORS_COUNT; j += 1u ) {
        Motion& mot = MOTION[j];

        tile = mot.tile_origin;
        next = tile + mot.step_input;

        if ( next[0] >= GRID_SIZE[0] ) mot.step_input[0] = 0;
        if ( next[1] >= GRID_SIZE[1] ) mot.step_input[1] = 0;

        if ( mot.step_input[0] != 0 || mot.step_input[1] != 0 ) {
            for ( u64 i = 0; i < DIRS_COUNT; i += 1u ) {
                part = mot.step_input * DIRS[i];
                next = tile + part;

                if ( indeces[next] != 0 )
                    mot.step_input -= part;
            }
        }
    }
}


void
move(Array2d<u64>& indeces, f64 time)
{
    f64   dist = 0;
    f64   incr = 0;
    Vec2f stop = {};

    for ( u64 j = 0; j < ACTORS_COUNT; j += 1u ) {
        Motion&   mot = MOTION[j];
        Position& pos = POSITION[j];

        if ( bit_test(mot.status, Motion::MOBILE) &&
             bit_test(mot.status, Motion::MOVING) == false ) {
            if ( mot.step_input != Vec2f {} ) {
                mot.tile_origin.from(pos / TILE_SIZE);
                mot.tile_finish = mot.tile_origin + mot.step_input;

                if ( indeces[mot.tile_finish] == 0 ) {
                    mot.step_value  = mot.step_input;
                    mot.speed_value = mot.speed_limit / mot.step_value.magnitude();
                    mot.status      = bit_write(mot.status, Motion::MOVING, 1);

                    indeces[mot.tile_finish] = j + 1u;
                    indeces[mot.tile_origin] = 0;
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
    u64     player;
    View    view;
    Grid    grid;
    Display display;
    Painter painter;
};

Title_State::Title_State()
    : player {0}
    , view {}
    , grid {}
    , display {}
    , painter {}
{
    Grid_Layer layer;

    grid.layers = Array<Grid_Layer>(LAYERS_COUNT);

    for ( u64 i = 0; i < grid.layers.size; i += 1u ) {
        layer.indeces = Array2d<u64>(GRID_SIZE);
        layer.actions = Array<Grid_Action*>(ACTIONS_COUNT);

        grid.push(layer);
    }

    grid.layers[0].push(&floor_layer_draw);
    grid.layers[1].push(&actor_layer_draw);
}

void
Title_State::startup()
{
    String title = String("Light", 0, 5u);
    u64    actor = 0;
    Vec2u  pos;

    for ( u64 i = 0; i < GRID_AREA; i += 1u )
        grid.layers[0].indeces[i] = rand() % COLOURS_COUNT;

    for ( u64 i = 0; i < ACTORS_COUNT; i += 1u ) {
        do {
            pos = {
                rand() % GRID_SIZE[0],
                rand() % GRID_SIZE[1],
            };

            actor = grid.layers[1].indeces[pos];
        } while ( actor != 0 );

        CONTROLS[i].motion    = &motion_func_random;
        MOTION[i].tile_origin = pos;
        MOTION[i].speed_limit = rand() % 10 * TILE_SIZE;
        MOTION[i].status      = bit_write(MOTION[i].status, Motion::MOBILE, MOTION[i].speed_limit != 0);
        COLOUR[i]             = {
            ((u8) rand() % 0x40) + 0xa0u,
            ((u8) rand() % 0x40) + 0xa0u,
            ((u8) rand() % 0x40) + 0xa0u,
            0xff,
        };

        POSITION[i].from(pos * TILE_SIZE);

        grid.layers[1].indeces[pos] = i + 1u;
    }

    CONTROLS[player].motion    = &motion_func_player;
    MOTION[player].speed_limit = 10.0 * TILE_SIZE;
    MOTION[player].status      = bit_write(MOTION[player].status, Motion::MOBILE, 1);
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
    collide(grid.layers[1].indeces);
    move(grid.layers[1].indeces, time);

    view.centre = POSITION[player] + TILE_HALF;
}

void
Title_State::after_step()
{
    Draw_Context context;
    Grid_Layer   layer;

    context.painter = &painter;
    context.view    = &view;

    painter.swap();

    for ( u64 j = 0; j < grid.count; j += 1u ) {
        layer = grid.layers[j];

        for ( u64 i = 0; i < layer.count; i += 1u )
            layer.actions[i](layer.indeces, &context);
    }

    painter.show();

    #define WRITE_WORLD 1

    #if WRITE_WORLD
        actor_layer_write(grid.layers[1].indeces, &context);
    #endif

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
