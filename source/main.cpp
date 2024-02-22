#include <light/Engine/import.hpp>

#include <time.h>  // time
#include <stdio.h> // printf

using namespace light;

using  Colour   = SDL_Color;
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

struct Tile
{
    u32 colour;
    u32 actor;
};

static const u32   TILE_SIZE   = 24u;        // Pixels.
static const Vec2u VIEW_SIZE   = {21u, 9u};  // Tiles.
static const Vec2u WINDOW_SIZE = {21u, 9u};  // Tiles.
static const Vec2u WORLD_SIZE  = {65u, 35u}; // Tiles.

static const u32   TILE_HALF   = TILE_SIZE / 2u;
static const Vec2u VIEW_HALF   = VIEW_SIZE / 2u;
static const Vec2u WINDOW_HALF = WINDOW_SIZE / 2u;

static const u32 WORLD_AREA = WORLD_SIZE[0] * WORLD_SIZE[1];

static const u32 ACTORS_COUNT = 20u;
static const u32 COLOURS_COUNT = 6u;

static const SDL_Color COLOURS[COLOURS_COUNT] = {
    {0x32, 0x70, 0x00, 0xff},
    {0x00, 0x70, 0x05, 0xff},
    {0x6a, 0x70, 0x00, 0xff},
    {0x6b, 0x34, 0x01, 0xff},
    {0x6b, 0x69, 0x01, 0xff},
    {0x6b, 0x01, 0x02, 0xff},
};

static const u8* KEYBOARD = 0;

static Array<Colour>   COLOUR   = Array<Colour>(ACTORS_COUNT);
static Array<Position> POSITION = Array<Position>(ACTORS_COUNT);
static Array<Movement> MOVEMENT = Array<Movement>(ACTORS_COUNT);

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

void
draw(SDL_Renderer* renderer, const View& view, const Array<Position>& position, const Array<Colour>& colour, const Array<Tile>& grid)
{
    Vec2f origin = view.origin();
    Vec4u bounds = view.visible(WORLD_SIZE * TILE_SIZE) / TILE_SIZE;

    u32              actor = 0;
    const SDL_Color* rgba  = 0;
    SDL_Rect         rect  = {0, 0, (s32) TILE_SIZE, (s32) TILE_SIZE};

    for ( u32 i = bounds[2]; i < bounds[3]; i += 1u ) {
        for ( u32 j = bounds[0]; j < bounds[1]; j += 1u ) {
            rgba = &COLOURS[grid[i * WORLD_SIZE[0] + j].colour];

            rect.x = j * TILE_SIZE - (s32) origin[0];
            rect.y = i * TILE_SIZE - (s32) origin[1];

            SDL_SetRenderDrawColor(renderer,
                rgba->r, rgba->g, rgba->b, rgba->a
            );

            SDL_RenderFillRect(renderer, &rect);
        }
    }

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);

    for ( u32 i = bounds[2]; i < bounds[3]; i += 1u ) {
        for ( u32 j = bounds[0]; j < bounds[1]; j += 1u ) {
            if ( grid[i * WORLD_SIZE[0] + j].actor == 0 ) continue;

            actor = grid[i * WORLD_SIZE[0] + j].actor - 1u;

            rect.x = (s32) position[actor][0] - (s32) origin[0];
            rect.y = (s32) position[actor][1] - (s32) origin[1];

            SDL_SetRenderDrawColor(renderer,
                colour[actor].r, colour[actor].g,
                colour[actor].b, colour[actor].a
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
    View          view;
    SDL_Window*   window;
    SDL_Renderer* renderer;
    Array<Tile>   grid;
};

Title_State::Title_State()
    : player {0}
    , view {}
    , window {0}
    , renderer {0}
    , grid {WORLD_AREA}
{}

void
Title_State::startup()
{
    String title = String("Light", 0, 5u);
    Vec2u  pos;

    for ( u32 i = 0; i < WORLD_AREA; i += 1u )
        grid[i].colour = rand() % COLOURS_COUNT;

    for ( u32 i = 0; i < ACTORS_COUNT; i += 1u ) {
        do {
            pos = {
                rand() % WORLD_SIZE[0],
                rand() % WORLD_SIZE[1],
            };
        } while ( grid[pos[1] * WORLD_SIZE[0] + pos[0]].actor != 0 );

        COLOUR[i]               = {(u8) (rand() % 0x80 + 0x80), (u8) (rand() % 0x80 + 0x80), (u8) (rand() % 0x80 + 0x80), 0xff};
        MOVEMENT[i].speed.limit = (f32) (rand() % 3u * 3u) * TILE_SIZE;
        POSITION[i]             = Vec2f::from(pos * TILE_SIZE);

        grid[pos[1] * WORLD_SIZE[0] + pos[0]].actor = i + 1u;
    }

    COLOUR[player]               = {0xff, 0xff, 0xff, 0xff};
    MOVEMENT[player].speed.limit = 10.f * TILE_SIZE;

    view.centre = POSITION[player] + TILE_HALF;
    view.unit = TILE_SIZE;
    view.size = Vec2f::from(VIEW_SIZE);

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

    u32   actor  = 0;
    Vec4u bounds = view.visible(WORLD_SIZE * TILE_SIZE) / TILE_SIZE;

    Vec2f target = {};
    Vec2f orient = {
        ((f32) KEYBOARD[SDL_SCANCODE_D] - KEYBOARD[SDL_SCANCODE_A]),
        ((f32) KEYBOARD[SDL_SCANCODE_S] - KEYBOARD[SDL_SCANCODE_W]),
    };

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

    view.centre = POSITION[player] + TILE_HALF;

    system("clear");

    for ( u32 i = 0; i < WORLD_SIZE[1]; i += 1u ) {
        for ( u32 j = 0; j < WORLD_SIZE[0]; j += 1u ) {
            actor = grid[i * WORLD_SIZE[0] + j].actor;

            if ( i >= bounds[2] && i < bounds[3] ) {
                if ( j >= bounds[0] && j < bounds[1] )
                    printf("\x1b[42m");
            }

            if ( actor != 0 ) {
                if ( actor == player + 1u )
                    printf("\x1b[41m");
                else
                    printf("\x1b[43m");

                printf("%2u\x1b[0m ", actor);
            } else
                printf("\x1b[90m ~\x1b[0m ");
        }

        printf("\n");
    }
}

void
Title_State::after_step()
{
    SDL_RenderClear(renderer);

    draw(renderer, view, POSITION, COLOUR, grid);

    SDL_RenderPresent(renderer);
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
    engine.execute(&title_state, 60u);

    SDL_Quit();

    return 0;
}
