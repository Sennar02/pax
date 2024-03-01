#include <light/Engine/import.hpp>

#include <time.h>  // time
#include <stdio.h> // printf

#include "game/Piece.hpp"

using namespace game;

static const u64   TILE_SIZE    = 48u;        // Pixels.
static const v2u64 GRID_SIZE    = {45u, 25u}; // Tiles.
static const v2u64 VIEW_SIZE    = {16u, 9u};  // Tiles.
static const v2u64 DISPLAY_SIZE = {16u, 9u};  // Tiles.

static const u64   TILE_HALF    = TILE_SIZE / 2u;
static const v2u64 GRID_HALF    = GRID_SIZE / 2u;
static const v2u64 VIEW_HALF    = VIEW_SIZE / 2u;
static const v2u64 DISPLAY_HALF = DISPLAY_SIZE / 2u;

static const u64 GRID_AREA =
    GRID_SIZE[0] * GRID_SIZE[1];

static const u64 ACTORS_COUNT      = 400u;
static const u64 GRID_LAYERS_COUNT = 2u;
static const u64 GRID_STEPS_COUNT  = 5u;

// TODO: Implement a tile system.
static const u64 COLOURS_COUNT = 4u;

// TODO: Implement a tile system.
static const v4u64 COLOURS_FLOOR[COLOURS_COUNT] = {
    {0x32, 0x70, 0x00, 0xff},
    {0x00, 0x70, 0x05, 0xff},
    {0x6a, 0x70, 0x00, 0xff},
    {0x6b, 0x34, 0x01, 0xff},
};

// TODO: Implement an input system.
static Array<const u8> KEYBOARD = Array<const u8>();

static Bump_Alloc memory = Bump_Alloc(calloc(1u, 1024u * 128u), 1024u * 128u);

static Array<v4u64>     COLOUR   = Array<v4u64>(ACTORS_COUNT, &memory);
static Array<Position>  POSITION = Array<Position>(ACTORS_COUNT, &memory);
static Array<Motion>    MOTION   = Array<Motion>(ACTORS_COUNT, &memory);
static Array<Controls*> CONTROLS = Array<Controls*>(ACTORS_COUNT, &memory);

struct Floor_Draw
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

public:
    void
    fixed_step(f64, Array2d<u64>&) {}

    /**
     *
     */
    void
    after_step(Array2d<u64>& table)
    {
        v4f64 bounds = view->bounds();
        v4u64 cull   = view->cull(bounds, {0, 0, table.cols, table.rows});
        v4u64 colour = {};
        v4f64 tile   = {};

        tile[2] = tile[3] = view->unit;

        for ( u64 r = cull[1]; r < cull[3]; r += 1u ) {
            for ( u64 c = cull[0]; c < cull[2]; c += 1u ) {
                colour = COLOURS_FLOOR[table[{c, r}]];

                tile[0] = c * tile[2] - bounds[0];
                tile[1] = r * tile[3] - bounds[1];

                painter->set_colour(colour);
                painter->fill_rect(tile);
            }
        }

        painter->set_colour();
    }
};

struct Actor_Draw
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

public:
    /**
     *
     */
    void
    fixed_step(f64, Array2d<u64>&) {}

    /**
     *
     */
    void
    after_step(Array2d<u64>& table)
    {
        v4f64    bounds = view->bounds();
        v4u64    cull   = view->cull(bounds, {0, 0, table.cols, table.rows});
        v4u64    colour = {};
        v4f64    tile   = {};
        u64      actor  = 0;
        Position point  = {};

        tile[2] = tile[3] = view->unit;

        for ( u64 r = cull[1]; r < cull[3]; r += 1u ) {
            for ( u64 c = cull[0]; c < cull[2]; c += 1u ) {
                actor = table[{c, r}];

                if ( actor != 0 ) {
                    point  = POSITION[actor - 1u];
                    colour = COLOUR[actor - 1u];

                    tile[0] = point[0] - bounds[0];
                    tile[1] = point[1] - bounds[1];

                    painter->set_colour(colour);
                    painter->fill_rect(tile);
                }
            }
        }

        painter->set_colour();
    }
};

struct Actor_Write
    : public Grid_Step
{
public:
    /**
     *
     */
    View* view = 0;

public:
    /**
     *
     */
    void
    fixed_step(f64, Array2d<u64>&)
    {}

    /**
     *
     */
    void
    after_step(Array2d<u64>& table)
    {
        v4f64 bounds = view->bounds();
        v4u64 cull   = view->cull(bounds, {0, 0, table.cols, table.rows});
        u64   index  = 0;

        system("clear");

        for ( u64 r = 0; r < table.rows; r += 1u ) {
            for ( u64 c = 0; c < table.cols; c += 1u ) {
                index = table[{c, r}];

                if ( c >= cull[0] && c < cull[2] &&
                     r >= cull[1] && r < cull[3] )
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
            cull[0], cull[1],
            cull[2], cull[3],
            view->factor
        );
    }
};

struct Player_Controls
    : public Controls
{
public:
    Array<const u8>* keyboard;

public:
    v2f64
    motion_step()
    {
        static const u64 NORTH = SDL_SCANCODE_W;
        static const u64 EAST  = SDL_SCANCODE_D;
        static const u64 SOUTH = SDL_SCANCODE_S;
        static const u64 WEST  = SDL_SCANCODE_A;

        return {
            (f64) ((*keyboard)[EAST]  - (*keyboard)[WEST]),
            (f64) ((*keyboard)[SOUTH] - (*keyboard)[NORTH]),
        };
    }
};

struct Random_Controls
    : public Controls
{
public:
    v2f64
    motion_step()
    {
        v2f64 res = {};

        if ( rand() % 5u == 0 )
            res = {rand() % 3 - 1.0, rand() % 3 - 1.0};

        return res;
    }
};

void
control()
{
    Motion    mot = {};
    Controls* ctl = 0;

    for ( u64 i = 0; i < ACTORS_COUNT; i += 1u ) {
        mot = MOTION[i];
        ctl = CONTROLS[i];

        if ( bits_test(mot.flag, Motion::MOBILE) )
            MOTION[i].step_input = ctl->motion_step();
    }
}

void
collide(Array2d<u64>& indeces)
{
    static const u64   DIRS_COUNT       = 3u;
    static const v2u64 DIRS[DIRS_COUNT] = {
        {1u, 0}, {0, 1u}, {1u, 1u},
    };

    v2u64 next = {};
    v2u64 tile = {};
    v2f64 part = {};

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
move(f64 time, Array2d<u64>& indeces)
{
    f64   dist = 0;
    f64   incr = 0;
    v2f64 stop = {};

    for ( u64 j = 0; j < ACTORS_COUNT; j += 1u ) {
        Motion&   mot = MOTION[j];
        Position& pos = POSITION[j];

        if ( bits_test(mot.flag, Motion::MOBILE) &&
             bits_test(mot.flag, Motion::MOVING) == false ) {
            if ( mot.step_input != v2f64 {} ) {
                mot.tile_origin.from(pos / TILE_SIZE);
                mot.tile_finish = mot.tile_origin + mot.step_input;

                if ( indeces[mot.tile_finish] == 0 ) {
                    mot.step_value  = mot.step_input;
                    mot.speed_value = mot.speed_limit / mot.step_value.magnitude();
                    mot.flag      = bits_write(mot.flag, Motion::MOVING, 1);

                    indeces[mot.tile_finish] = j + 1u;
                    indeces[mot.tile_origin] = 0;
                }
            }
        }

        if ( bits_test(mot.flag, Motion::MOVING) ) {
            stop.from(mot.tile_finish * TILE_SIZE);

            for ( u64 i = 0; i < mot.step_value.SIZE; i += 1u ) {
                incr = mot.step_value[i] * mot.speed_value * time;
                dist = abs(stop[i] - pos[i]);

                pos[i] += incr;

                if ( dist < abs(incr) )
                    pos[i] = stop[i];
            }

            if ( pos == stop ) {
                mot.flag      = bits_write(mot.flag, Motion::MOVING, 0);
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

    #define LIGHT_WRITE_ACTORS true

    #if LIGHT_WRITE_ACTORS
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
    SDL_Event event;

    while ( SDL_PollEvent(&event) ) {
        if ( event.type == SDL_QUIT ) return false;

        if ( event.type == SDL_KEYUP ) {
            if ( event.key.keysym.sym == SDLK_ESCAPE )
                return false;
        }

        if ( event.type == SDL_MOUSEWHEEL ) {
            view.factor = light_max(
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

    SDL_PumpEvents();

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

int
main(int, const char*[])
{
    Title_State title_state;
    Engine      engine;
    s32         size = 0;

    srand( time(0) );

    if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        printf("%s\n", SDL_GetError());

        return -1;
    }

    KEYBOARD.data = SDL_GetKeyboardState(&size);
    KEYBOARD.size = size;

    engine.execute(&title_state, 64u);

    SDL_Quit();

    free(memory.data);

    return 0;
}
