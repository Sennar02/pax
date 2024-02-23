#include <light/Engine/import.hpp>

#include <time.h>  // time
#include <stdio.h> // printf

using namespace light;

using  Position = Vec2f;
struct Movement
{
    struct {
        f32 limit;
        f32 value;
    } speed;

    Vec2f    orient;
    Vec2f    target;
    bool     moving;
};

struct Grid_Layer
{
public:
    Array<u32> tiles;

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

static const u32   TILE_SIZE   = 48u;        // Pixels.
static const Vec2u VIEW_SIZE   = {16u, 9u};  // Tiles.
static const Vec2u WINDOW_SIZE = {16u, 9u};  // Tiles.
static const Vec2u WORLD_SIZE  = {65u, 35u}; // Tiles.

static const u32   TILE_HALF   = TILE_SIZE / 2u;
static const Vec2u VIEW_HALF   = VIEW_SIZE / 2u;
static const Vec2u WINDOW_HALF = WINDOW_SIZE / 2u;

static const u32 WORLD_AREA = WORLD_SIZE[0] * WORLD_SIZE[1];

static const u32 ACTORS_COUNT = 20u;
static const u32 COLOURS_COUNT = 4u;

static const Vec4u COLOURS_FLOOR[COLOURS_COUNT] = {
    {0x32, 0x70, 0x00, 0xff},
    {0x00, 0x70, 0x05, 0xff},
    {0x6a, 0x70, 0x00, 0xff},
    {0x6b, 0x34, 0x01, 0xff},
};

static const u8* KEYBOARD = 0;

static Array<Vec4u>    COLOUR   = Array<Vec4u>(ACTORS_COUNT);
static Array<Position> POSITION = Array<Position>(ACTORS_COUNT);
static Array<Movement> MOVEMENT = Array<Movement>(ACTORS_COUNT);

void
Floor_Layer::draw(const View& view, Painter& painter) const
{
    Vec2f origin      = view.origin();
    Vec4u limits      = view.visible(WORLD_SIZE);
    Vec4f tile        = {};
    const Vec4u* rgba = 0;
    u32   index       = 0;

    tile[2] = tile[3] = view.unit;

    for ( u32 i = limits[2]; i < limits[3]; i += 1u ) {
        for ( u32 j = limits[0]; j < limits[1]; j += 1u ) {
            index = i * WORLD_SIZE[0] + j;
            index = tiles[index];
            rgba  = &COLOURS_FLOOR[index];

            tile[0] = j * view.unit - origin[0];
            tile[1] = i * view.unit - origin[1];

            painter.set_colour(*rgba);
            painter.draw_rect_full(tile);
        }
    }

    painter.set_colour({});
}

void
Actor_Layer::draw(const View& view, Painter& painter) const
{
    Vec2f origin      = view.origin();
    Vec4u limits      = view.visible(WORLD_SIZE);
    Vec4f tile        = {};
    const Vec4u* rgba = 0;
    u32   index       = 0;
    u32   actor       = 0;

    tile[2] = tile[3] = view.unit;

    for ( u32 i = limits[2]; i < limits[3]; i += 1u ) {
        for ( u32 j = limits[0]; j < limits[1]; j += 1u ) {
            index = i * WORLD_SIZE[0] + j;
            index = tiles[index];
            actor = index - 1u;

            if ( index != 0 ) {
                rgba = &COLOUR[actor];

                tile[0] = POSITION[actor][0] - origin[0];
                tile[1] = POSITION[actor][1] - origin[1];

                painter.set_colour(*rgba);
                painter.draw_rect_full(tile);
            }
        }
    }

    painter.set_colour({});
}

/*
void
move(f32 step, Vec2f orient, u32 actor, Array<Position>& position, Array<Movement>& movement, Array<Tile>& grid)
{
    Vec2f dist = {};
    Vec2f incr = {};
    Vec2u next = {};

    if ( movement[actor].moving ) {
        incr = movement[actor].orient * movement[actor].speed.value * step;
        dist = movement[actor].target - position[actor];

        for ( u32 i = 0; i < Vec2f::SIZE; i += 1u ) {
            if ( abs(dist[i]) <= abs(incr[i]) )
                position[actor][i] = movement[actor].target[i];
            else
                position[actor][i] += incr[i];
        }

        if ( position[actor] == movement[actor].target )
            movement[actor].moving = false;
    } else {
        for ( u32 i = 0; i < Vec2f::SIZE; i += 1u ) {
            next = Vec2u::from(position[actor] / TILE_SIZE);
            next[i] += (u32) orient[i];

            if ( grid[next[1] * WORLD_SIZE[0] + next[0]].actor != 0 )
                orient[i] = 0;
        }

        next = Vec2u::from(position[actor] / TILE_SIZE + orient);

        if ( grid[next[1] * WORLD_SIZE[0] + next[0]].actor != 0 )
            orient = {};

        if ( orient != Vec2f {} ) {
            movement[actor].speed.value = movement[actor].speed.limit / orient.magnitude();
            movement[actor].target      = position[actor] + orient * TILE_SIZE;
            movement[actor].orient      = orient;
            movement[actor].moving      = true;

            grid[next[1] * WORLD_SIZE[0] + next[0]].actor = actor + 1u;

            next = Vec2u::from(position[actor] / TILE_SIZE);

            grid[next[1] * WORLD_SIZE[0] + next[0]].actor = 0;
        }
    }
}
*/

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
    fixed_step(f32 step, u32 skip);

    void
    after_step();

private:
    u32         player;
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
    floor_layer.tiles = Array<u32>(WORLD_AREA);
    actor_layer.tiles = Array<u32>(WORLD_AREA);
}

void
Title_State::startup()
{
    String title = String("Light", 0, 5u);
    u32    index = 0;
    u32    actor = 0;
    Vec2u  pos;

    for ( u32 i = 0; i < WORLD_AREA; i += 1u )
        floor_layer.tiles[i] = rand() % COLOURS_COUNT;

    for ( u32 i = 0; i < ACTORS_COUNT; i += 1u ) {
        do {
            pos = {
                rand() % WORLD_SIZE[0],
                rand() % WORLD_SIZE[1],
            };

            index = pos[1] * WORLD_SIZE[0] + pos[0];
            actor = actor_layer.tiles[index];
        } while ( actor != 0 );

        COLOUR[i]               = {(u8) (rand() % 0x80 + 0x80), (u8) (rand() % 0x80 + 0x80), (u8) (rand() % 0x80 + 0x80), 0xff};
        MOVEMENT[i].speed.limit = (f32) (rand() % 3u * 3u) * TILE_SIZE;
        POSITION[i]             = Vec2f::from(pos * TILE_SIZE);

        actor_layer.tiles[index] = i + 1u;
    }

    COLOUR[player]               = {0xff, 0xff, 0xff, 0xff};
    MOVEMENT[player].speed.limit = 10.f * TILE_SIZE;

    view.centre = POSITION[player] + TILE_HALF;
    view.unit   = TILE_SIZE;
    view.size   = VIEW_SIZE;

    display.create(title, WINDOW_SIZE * TILE_SIZE);

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
Title_State::fixed_step(f32 step, u32 skip)
{
    SDL_PumpEvents();

    u32   index  = 0;
    Vec4u limits = view.visible(WORLD_SIZE);
    Vec2f target = {};
    Vec2f orient = {
        ((f32) KEYBOARD[SDL_SCANCODE_D] - KEYBOARD[SDL_SCANCODE_A]),
        ((f32) KEYBOARD[SDL_SCANCODE_S] - KEYBOARD[SDL_SCANCODE_W]),
    };

/*
    for ( u32 i = 0; i < ACTORS_COUNT; i += 1u ) {
        if ( i != player )
            orient = {rand() % 3u - 1.f, rand() % 3u - 1.f};

        if ( MOVEMENT[i].speed.limit != 0 ) {
            target = POSITION[i] + orient * TILE_SIZE;

            for ( u32 j = 0; j < Vec2f::SIZE; j += 1u ) {
                if ( target[j] < 0 || target[j] >= WORLD_SIZE[j] * TILE_SIZE )
                    orient[j] = 0;
            }

            move(step, orient, i, POSITION, MOVEMENT, grid);
        }
    }
*/
    view.centre += orient * 10.f * TILE_SIZE * step;

/*
    system("clear");

    for ( u32 i = 0; i < WORLD_SIZE[1]; i += 1u ) {
        for ( u32 j = 0; j < WORLD_SIZE[0]; j += 1u ) {
            index = i * WORLD_SIZE[0] + j;
            index = actor_layer.tiles[index];

            if ( i >= limits[2] && i < limits[3] &&
                 j >= limits[0] && j < limits[1])
                printf("\x1b[46m");

            if ( index != 0 )
                printf("\x1b[93m%2u\x1b[0m ", index);
            else
                printf("\x1b[90m ~\x1b[0m ");
        }

        printf("\n");
    }

    printf("[%u, %u) x [%u, %u)\n",
        limits[0], limits[1],
        limits[2], limits[3]
    );
*/
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

    srand(time(0));

    if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        printf("%s\n", SDL_GetError());

        return -1;
    }

    KEYBOARD = SDL_GetKeyboardState(0);
    engine.execute(&title_state, 144u);

    SDL_Quit();

    return 0;
}
