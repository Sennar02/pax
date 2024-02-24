#include <light/Engine/import.hpp>

#include <time.h>  // time
#include <stdio.h> // printf

using namespace light;

using  Position = Vec2f;
struct Movement
{
    struct {
        f64 limit;
        f64 value;
    } speed;

    Vec2f target;
    Vec2f orient;
    Vec2f next;
    bool  moving;
};

struct Controls
{
public:
    virtual Vec2f
    orient() = 0;
};

struct Player_Controls
    : public Controls
{
public:
    Vec2f
    orient();
};

struct Random_Controls
    : public Controls
{
public:
    Vec2f data;

public:
    Vec2f
    orient();
};

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

static const u64   TILE_SIZE   = 48u;        // Pixels.
static const Vec2u VIEW_SIZE   = {16u, 9u};  // Tiles.
static const Vec2u WINDOW_SIZE = {16u, 9u};  // Tiles.
static const Vec2u WORLD_SIZE  = {65u, 35u}; // Tiles.

static const u64   TILE_HALF   = TILE_SIZE / 2u;
static const Vec2u VIEW_HALF   = vec_sdiv_scale(VIEW_SIZE, 2u);
static const Vec2u WINDOW_HALF = vec_sdiv_scale(WINDOW_SIZE, 2u);

static const u64 WORLD_AREA = WORLD_SIZE[0] * WORLD_SIZE[1];

static const u64 ACTORS_COUNT = 50u;
static const u64 COLOURS_COUNT = 4u;

static const Vec4u COLOURS_FLOOR[COLOURS_COUNT] = {
    {0x32, 0x70, 0x00, 0xff},
    {0x00, 0x70, 0x05, 0xff},
    {0x6a, 0x70, 0x00, 0xff},
    {0x6b, 0x34, 0x01, 0xff},
};

static const u8* KEYBOARD = 0;

static Array<Vec4u>     COLOUR   = Array<Vec4u>(ACTORS_COUNT);
static Array<Position>  POSITION = Array<Position>(ACTORS_COUNT);
static Array<Movement>  MOVEMENT = Array<Movement>(ACTORS_COUNT);
static Array<Controls*> CONTROLS = Array<Controls*>(ACTORS_COUNT);

static Player_Controls player_controls;
static Random_Controls random_controls;

Vec2f
Player_Controls::orient()
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
Random_Controls::orient()
{
    if ( rand() % 35u == 0 )
        data = {rand() % 3u - 1.0, rand() % 3u - 1.0};

    return data;
}

void
Floor_Layer::draw(const View& view, Painter& painter) const
{
    Vec2f origin = view.origin();
    Vec4u limits = view.visible(WORLD_SIZE);
    Vec2f offset = {};
    Vec4f tile   = {};
    Vec4u rgba   = {};
    u64   index  = 0;

    offset.from(vec_sub(WINDOW_HALF, VIEW_HALF));
    offset = vec_smul_scale(offset, TILE_SIZE);

    tile[2] = tile[3] = view.unit;

    for ( u64 j = limits[2]; j < limits[3]; j += 1u ) {
        for ( u64 i = limits[0]; i < limits[1]; i += 1u ) {
            index = grid[{i, j}];
            rgba  = COLOURS_FLOOR[index];

            tile[0] = i * view.unit - origin[0] + offset[0];
            tile[1] = j * view.unit - origin[1] + offset[1];

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
    Vec4u limits = view.visible(WORLD_SIZE);
    Vec2f offset = {};
    Vec4f tile   = {};
    Vec4u rgba   = {};
    u64   index  = 0;
    u64   actor  = 0;

    offset.from(vec_sub(WINDOW_HALF, VIEW_HALF));
    offset = vec_smul_scale(offset, TILE_SIZE);

    tile[2] = tile[3] = view.unit;

    for ( u64 j = limits[2]; j < limits[3]; j += 1u ) {
        for ( u64 i = limits[0]; i < limits[1]; i += 1u ) {
            index = grid[{i, j}];
            actor = index - 1u;

            if ( index != 0 ) {
                rgba = COLOUR[actor];

                tile[0] = POSITION[actor][0] - origin[0] + offset[0];
                tile[1] = POSITION[actor][1] - origin[1] + offset[1];

                painter.set_colour(rgba);
                painter.draw_rect_full(tile);
            }
        }
    }

    painter.set_colour({});
}

void
controls()
{
    Vec2f orient = {};
    Vec2u tile = {};

    for ( u64 i = 0; i < ACTORS_COUNT; i += 1u ) {
        Movement& mov = MOVEMENT[i];
        Position& pos = POSITION[i];
        Controls* ctl = CONTROLS[i];

        if ( mov.speed.limit == 0 ) continue;

        if ( mov.moving == false ) {
            orient = ctl->orient();

            tile.from(vec_sdiv_scale(pos, TILE_SIZE));
            tile = vec_add(tile, orient);

            if ( tile[0] < WORLD_SIZE[0] && tile[1] < WORLD_SIZE[1] )
                mov.target = orient;
        }
    }
}

void
collide(Grid_Layer& layer)
{
    static const u64   DIRS_COUNT       = 3u;
    static const Vec2u DIRS[DIRS_COUNT] = {{1u, 0}, {0, 1u}, {1u, 1u}};

    Vec2u next = {};
    Vec2u tile = {};
    Vec2f comp = {};

    for ( u64 j = 0; j < ACTORS_COUNT; j += 1u ) {
        Movement& mov = MOVEMENT[j];
        Position& pos = POSITION[j];

        tile.from(vec_sdiv_scale(pos, TILE_SIZE));

        for ( u64 i = 0; i < DIRS_COUNT; i += 1u ) {
            comp = vec_mul_scale(mov.target, DIRS[i]);
            next = vec_add(tile, comp);

            if ( layer.grid[next] != 0 )
                mov.target = vec_sub(mov.target, comp);
        }
    }
}


void
move(Grid_Layer& layer, f64 step)
{
    Vec2f dist = {};
    Vec2f incr = {};
    Vec2u tile = {};
    Vec2u next = {};

    for ( u64 j = 0; j < ACTORS_COUNT; j += 1u ) {
        Movement& mov = MOVEMENT[j];
        Position& pos = POSITION[j];

        if ( mov.moving == false ) {
            if ( mov.target != Vec2f {} ) {
                mov.orient      = mov.target;
                mov.speed.value = mov.speed.limit / mov.orient.magnitude();
                mov.next        = vec_add(pos, vec_smul_scale(mov.orient, TILE_SIZE));
                mov.moving      = true;

                tile.from(vec_sdiv_scale(pos, TILE_SIZE));
                next = vec_add(tile, mov.orient);

                layer.grid[tile] = 0;
                layer.grid[next] = j + 1u;
            }
        } else {
            incr = vec_smul_scale(mov.orient, mov.speed.value * step);
            dist = vec_sub(mov.next, pos);

            for ( u64 i = 0; i < incr.SIZE; i += 1u ) {
                if ( abs(incr[i]) < abs(dist[i]) )
                    pos[i] += incr[i];
                else
                    pos[i] = mov.next[i];
            }

            if ( pos == mov.next ) mov.moving = false;
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
    fixed_step(f64 step, u64 skip);

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
    floor_layer.grid = Array2d<u64>(WORLD_SIZE);
    actor_layer.grid = Array2d<u64>(WORLD_SIZE);
}

void
Title_State::startup()
{
    String title = String("Light", 0, 5u);
    u64    actor = 0;
    Vec2u  pos;

    for ( u64 i = 0; i < WORLD_AREA; i += 1u )
        floor_layer.grid[i] = rand() % COLOURS_COUNT;

    for ( u64 i = 0; i < ACTORS_COUNT; i += 1u ) {
        do {
            pos = {
                rand() % WORLD_SIZE[0],
                rand() % WORLD_SIZE[1],
            };

            actor = actor_layer.grid[pos];
        } while ( actor != 0 );

        COLOUR[i]               = {(u8) (rand() % 0x80 + 0x80), (u8) (rand() % 0x80 + 0x80), (u8) (rand() % 0x80 + 0x80), 0xff};
        MOVEMENT[i].speed.limit = TILE_SIZE;
        POSITION[i].from(vec_smul_scale(pos, TILE_SIZE));
        CONTROLS[i] = &random_controls;

        actor_layer.grid[pos] = i + 1u;
    }

    COLOUR[player]               = {0xff, 0xff, 0xff, 0xff};
    CONTROLS[player] = &player_controls;

    view.centre = vec_sadd(POSITION[player], TILE_HALF);
    view.unit   = TILE_SIZE;
    view.size   = VIEW_SIZE;

    display.create(title,
        vec_smul_scale(WINDOW_SIZE, TILE_SIZE)
    );

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
Title_State::fixed_step(f64 step, u64 skip)
{
    SDL_PumpEvents();

    controls();
    collide(actor_layer);
    move(actor_layer, step * skip);

    view.centre = vec_sadd(POSITION[player], TILE_HALF);

#define PRINT_WORLD 0

#if PRINT_WORLD
    u64   index  = 0;
    Vec4u limits = view.visible(WORLD_SIZE);

    system("clear");

    for ( u64 j = 0; j < WORLD_SIZE[1]; j += 1u ) {
        for ( u64 i = 0; i < WORLD_SIZE[0]; i += 1u ) {
            index = actor_layer.grid[{i, j}];

            if ( i >= limits[0] && i < limits[1] &&
                 j >= limits[2] && j < limits[3])
                printf("\x1b[46m");

            if ( index != 0 )
                printf("\x1b[93m%2lu\x1b[0m ", index);
            else
                printf("\x1b[90m ~\x1b[0m ");
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
