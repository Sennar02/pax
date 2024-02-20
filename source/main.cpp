#include <light/Engine/import.hpp>

#include <time.h>  // time
#include <stdio.h> // printf

#include <SDL2/SDL.h>

using namespace light;

static const u32   TILE_SIZE   = 48u;        // Pixels.
static const Vec2u WINDOW_SIZE = {20u, 12u};  // Tiles.
static const Vec2u CAMERA_SIZE = {16u, 9u};  // Tiles.
static const Vec2u WORLD_SIZE  = {50u, 35u}; // Tiles.

static const u32   TILE_HALF   = TILE_SIZE / 2u;
static const Vec2u WINDOW_HALF = WINDOW_SIZE / 2u;
static const Vec2u CAMERA_HALF = CAMERA_SIZE / 2u;

static const u32 WORLD_AREA = WORLD_SIZE[0] * WORLD_SIZE[1];

static const u32 ACTORS_COUNT = 25u;
static const u32 COLORS_COUNT = 3u;

static const SDL_Color COLORS[COLORS_COUNT] = {
    {0xffu, 0x00u, 0x00u, 0xffu},
    {0xffu, 0xffu, 0x00u, 0xffu},
    {0xffu, 0x60u, 0x20u, 0xffu},
};

static const u8* keyboard = 0;

using Position = Vec2f;

struct Velocity
{
    f32 limit;
    f32 value;
};

struct Movement
{
    Position pos;
    Velocity vel;
    Vec2f    dir;
    Vec2f    target;
    bool     moving;
};

using Color = SDL_Color;

struct Actor
{
    Movement movement;
    Color    color;
};

struct Tile
{
    u32 color;
    u32 actor;
};

void
move(f32 step, Vec2f dir, u32 actor, Array<Actor>& actors, Array<Tile>& grid)
{
    Vec2f dist = {};
    Vec2f incr = {};
    Vec2u next = {};

    if ( actors[actor].movement.moving ) {
        incr = actors[actor].movement.dir * actors[actor].movement.vel.value * step;
        dist = actors[actor].movement.target - actors[actor].movement.pos;

        for ( u32 i = 0; i < Vec2f::SIZE; i += 1u ) {
            if ( abs(dist[i]) <= abs(incr[i]) )
                actors[actor].movement.pos[i] = actors[actor].movement.target[i];
            else
                actors[actor].movement.pos[i] += incr[i];
        }

        if ( actors[actor].movement.pos == actors[actor].movement.target )
            actors[actor].movement.moving = false;
    } else {
        for ( u32 i = 0; i < Vec2f::SIZE; i += 1u ) {
            next = {
                (u32) actors[actor].movement.pos[0] / TILE_SIZE,
                (u32) actors[actor].movement.pos[1] / TILE_SIZE,
            };

            next[i] += (u32) dir[i];

            if ( grid[next[1] * WORLD_SIZE[0] + next[0]].actor != 0 )
                dir[i] = 0;
        }

        next = {
            (u32) (actors[actor].movement.pos[0] / TILE_SIZE + dir[0]),
            (u32) (actors[actor].movement.pos[1] / TILE_SIZE + dir[1]),
        };

        if ( grid[next[1] * WORLD_SIZE[0] + next[0]].actor != 0 )
            dir = {};

        if ( dir != Vec2f {} ) {
            actors[actor].movement.target    = actors[actor].movement.pos + dir * TILE_SIZE;
            actors[actor].movement.vel.value = actors[actor].movement.vel.limit / dir.magnitude();
            actors[actor].movement.dir       = dir;
            actors[actor].movement.moving    = true;

            grid[next[1] * WORLD_SIZE[0] + next[0]].actor = actor + 1u;

            next = {
                (u32) actors[actor].movement.pos[0] / TILE_SIZE,
                (u32) actors[actor].movement.pos[1] / TILE_SIZE,
            };

            grid[next[1] * WORLD_SIZE[0] + next[0]].actor = 0;
        }
    }
}

void
draw(SDL_Renderer* renderer, const Camera& camera, const Array<Tile>& grid, const Array<Actor>& actors)
{
    Vec2f origin = camera.top_left();
    Vec4u bounds = camera.bounds(TILE_SIZE, WORLD_SIZE);
    Vec2u offset = {
        (u32) (WINDOW_HALF[0] - CAMERA_HALF[0]) * TILE_SIZE,
        (u32) (WINDOW_HALF[1] - CAMERA_HALF[1]) * TILE_SIZE,
    };

    const SDL_Color* color = 0;
    const Actor*     actor = 0;
    SDL_Rect         rect  = {0, 0, (s32) TILE_SIZE, (s32) TILE_SIZE};

    for ( u32 i = bounds[2]; i < bounds[3]; i += 1u ) {
        for ( u32 j = bounds[0]; j < bounds[1]; j += 1u ) {
            color = &COLORS[grid[i * WORLD_SIZE[0] + j].color];

            rect.x = j * TILE_SIZE + offset[0] - (s32) origin[0];
            rect.y = i * TILE_SIZE + offset[1] - (s32) origin[1];

            SDL_SetRenderDrawColor(renderer,
                color->r, color->g, color->b, color->a
            );

            SDL_RenderFillRect(renderer, &rect);
        }
    }

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);

    for ( u32 i = bounds[2]; i < bounds[3]; i += 1u ) {
        for ( u32 j = bounds[0]; j < bounds[1]; j += 1u ) {
            if ( grid[i * WORLD_SIZE[0] + j].actor == 0 ) continue;

            actor = &actors[grid[i * WORLD_SIZE[0] + j].actor - 1u];

            rect.x = actor->movement.pos[0] + offset[0] - (s32) origin[0];
            rect.y = actor->movement.pos[1] + offset[1] - (s32) origin[1];

            SDL_SetRenderDrawColor(renderer,
                actor->color.r, actor->color.g,
                actor->color.b, actor->color.a
            );

            SDL_RenderFillRect(renderer, &rect);
        }
    }

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
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
    fixed_step(f32 step, u32 skip);

    void
    after_step();

private:
    u32           player;
    Camera        camera;
    SDL_Window*   window;
    SDL_Renderer* renderer;
    Array<Actor>  actors;
    Array<Tile>   grid;
};

Title_State::Title_State()
    : player {0}
    , camera {}
    , window {0}
    , renderer {0}
    , actors {ACTORS_COUNT}
    , grid {WORLD_AREA}
{}

void
Title_State::startup()
{
    String title = String("Light", 0, 5u);

    for ( u32 i = 0; i < WORLD_AREA; i += 1u )
        grid[i].color = rand() % COLORS_COUNT;

    for ( u32 i = 0; i < actors.size; i += 1u ) {
        Vec2u pos = {
            rand() % WORLD_SIZE[0],
            rand() % WORLD_SIZE[1],
        };

        actors[i].color = {(u8) (rand() % 0x80 + 0x40), (u8) (rand() % 0x80 + 0x40), (u8) (rand() % 0x80 + 0x40), 0xff};
        actors[i].movement.vel.limit = (f32) (rand() % 3u * 3u) * TILE_SIZE;
        actors[i].movement.pos = {
            (f32) pos[0] * TILE_SIZE,
            (f32) pos[1] * TILE_SIZE,
        };

        grid[pos[1] * WORLD_SIZE[0] + pos[0]].actor = i + 1u;
    }

    actors[player].color = {0xff, 0xff, 0xff, 0xff};
    actors[player].movement.vel.limit = 10.f * TILE_SIZE;
    camera.center = actors[player].movement.pos + TILE_HALF;
    camera.offset = {
        (f32) CAMERA_HALF[0] * TILE_SIZE,
        (f32) CAMERA_HALF[1] * TILE_SIZE,
    };

    window = SDL_CreateWindow(title.data,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_SIZE[0] * TILE_SIZE,
        WINDOW_SIZE[1] * TILE_SIZE,
        0
    );

    if ( window != 0 ) {
        renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED
        );

        if ( renderer == 0 )
            SDL_DestroyWindow(window);
    }
}

void
Title_State::cleanup()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
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

    Vec4u bounds = camera.bounds(TILE_SIZE, WORLD_SIZE);

    Vec2f target = {};
    Vec2f dir    = {
        ((f32) keyboard[SDL_SCANCODE_D] - keyboard[SDL_SCANCODE_A]),
        ((f32) keyboard[SDL_SCANCODE_S] - keyboard[SDL_SCANCODE_W]),
    };

    system("clear");
    printf("%f times %u\n", step, skip);

    for ( u32 i = 0; i < actors.size; i += 1u ) {
        if ( i != player )
            dir = {rand() % 3u - 1.f, rand() % 3u - 1.f};

        if ( actors[i].movement.vel.limit != 0 ) {
            target = actors[i].movement.pos + dir * TILE_SIZE;

            for ( u32 j = 0; j < Vec2f::SIZE; j += 1u ) {
                if ( target[j] < 0 || target[j] >= WORLD_SIZE[j] * TILE_SIZE )
                    dir[j] = 0;
            }

            move(step, dir, i, actors, grid);
        }
    }

    camera.center = actors[player].movement.pos + TILE_HALF;

    for ( u32 i = 0; i < WORLD_SIZE[1]; i += 1u ) {
        for ( u32 j = 0; j < WORLD_SIZE[0]; j += 1u ) {
            if ( grid[i * WORLD_SIZE[0] + j].actor != 0 ) {
                if ( grid[i * WORLD_SIZE[0] + j].actor == player + 1u )
                    printf("\x1b[32m");
                else
                    printf("\x1b[31m");
            }

            if ( i >= bounds[2] && i < bounds[3] ) {
                if ( j >= bounds[0] && j < bounds[1] )
                    printf("\x1b[44m");
            }

            printf("%2u\x1b[0m ", grid[i * WORLD_SIZE[0] + j].actor);
        }

        printf("\n");
    }
}

void
Title_State::after_step()
{
    SDL_RenderClear(renderer);

    draw(renderer, camera, grid, actors);

    SDL_RenderPresent(renderer);
}

int
main(int, const char*[])
{
    Title_State title_state;
    Engine      engine;

    srand(time(0));

    SDL_Init(SDL_INIT_EVERYTHING);
    keyboard = SDL_GetKeyboardState(0);

    engine.execute(&title_state, 40u);

    SDL_Quit();

    return 0;
}
