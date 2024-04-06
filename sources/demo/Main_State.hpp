#ifndef DEMO_MAIN_STATE_HPP
#define DEMO_MAIN_STATE_HPP

#include "define.hpp"
#include "Position.hpp"
#include "Movement.hpp"

// time.
#include <time.h>

struct Main_State
    : public State
{
public:
    /**
     * Pool of three colours for the ground tiles.
     */
    static const Store<Colour, 3u> GROUND_COLOURS;

public:
    /**
     * Display where the game is painted.
     */
    Display display;

    /**
     * Painter which paints the game on the display.
     */
    Painter painter;

    /**
     * todo: Comment.
     */
    Dispatcher dispat;

    /**
     * todo: Comment.
     */
    View view;

    /**
     * Helper which determines if the game is still running.
     */
    bool active = true;

    /**
     * Grid for the ground tiles.
     */
    Array2d<u64> ground;

    /**
     * Grid for the actors' collision detection.
     */
    Array2d<u64> actors;

    /**
     * Pool of position components.
     */
    Array<Position> position;

    /**
     * Pool of movement components.
     */
    Array<Movement> movement;

    /**
     * Pool of colour components.
     */
    Array<Colour> colour;

public:
    /**
     * Acquires the necessary resources.
     */
    void
    acquire();

    /**
     * Releases the resources.
     */
    void
    release();

    /**
     * todo: Comment.
     */
    bool
    input();

    /**
     * todo: Comment.
     */
    void
    fixed_step(f64 time);

    /**
     * todo: Comment.
     */
    void
    after_step();

    /**
     * todo: Comment.
     */
    void
    actors_show();

    /**
     * todo: Comment.
     */
    void
    actors_control();

    /**
     * todo: Comment.
     */
    void
    actors_collide();

    /**
     * todo: Comment.
     */
    void
    actors_move(f64 time);

    /**
     * todo: Comment.
     */
    void
    ground_paint();

    /**
     * todo: Comment.
     */
    void
    actors_paint();
};

void
on_keybd_event(Keybd_Event event, Main_State* state)
{
    if ( event.is_press() ) return;

    if ( event.code == Keybd::ESC )
        state->active = false;
}

void
on_display_event(Display_Event event, Main_State* state)
{
    if ( event.is_close() ) state->active = false;
}

void
on_mouse_event(Mouse_Event event, Main_State* state)
{
    v2f64 scale = state->view.scale;
    f64   extra = 1;

    if ( is_keybd_press(Keybd::Z) )
        extra *= 10;

    scale += scale * event.scroll(1) * extra * 0.1;
    scale = {
        pax_min(100.0, pax_max(0.01, scale(0))),
        pax_min(100.0, pax_max(0.01, scale(1))),
    };

    if ( event.button == Mouse::BTN_CENTRE )
        scale = {1.0, 1.0};

    state->view.scale = scale;
    state->painter.set_scale(state->view.scale);
}

const Store<Colour, 3u> Main_State::GROUND_COLOURS = {
    Colour {0x32, 0x70, 0x00, 0xff},
    Colour {0x00, 0x70, 0x05, 0xff},
    Colour {0x6a, 0x70, 0x00, 0xff},
};

void
Main_State::acquire()
{
    Monitor monitor;

    monitor.index = 1;

    // Creates the grids.
    ground = array2d_create<u64>(PAX_GRID_SIZE);
    actors = array2d_create<u64>(PAX_GRID_SIZE);

    // Creates the pools.
    position = array_create<Position>(PAX_MAX_ACTORS);
    movement = array_create<Movement>(PAX_MAX_ACTORS);
    colour   = array_create<Colour>(PAX_MAX_ACTORS);

    srand(time(0));

    // Fills with random indeces used to access the GROUND_COLOURS array.
    for ( u64 i = 0; i < ground.area; i += 1u )
        ground(i) = rand() % GROUND_COLOURS.SIZE;

    // Fills the grid with all the actors' indeces and fills the pool with all the points creating
    // a bijection between every actor and its position in the grid.
    for ( u64 i = 0; i < position.size; i += 1u ) {
        v2u64 tile = {};

        do {
            tile(0) = rand() % actors.size(0);
            tile(1) = rand() % actors.size(1);
        } while ( actors(tile) != 0 );

        position(i).point = tile;
        actors(tile) = i + 1u;
    }

    // Fills the movement pool with the same speed limit, if its limit is zero the actor is also immobile.
    for ( u64 i = 0; i < movement.size; i += 1u ) {
        u64 limit = rand() % 2;
        u64 scale = rand() % 7 + 1;

        if ( i == 0 ) {
            limit = 1;
            scale = 7;
        }

        movement(i).set_mobile(limit != 0);
        movement(i).limit = limit * scale;
    }

    // Fills the colour pool with random colours, the player is always white.
    for ( u64 i = 0; i < colour.size; i += 1u ) {
        for ( u64 c = 0; c < Colour::SIZE; c += 1u )
            colour(i)(c) = (u8) rand() % 0x40 + 0xa0;

        if ( i == 0 )
            colour(i) = {0xff, 0xff, 0xff, 0xff};
    }

    // Prepares the view with centre on the player.
    view.offset = PAX_VIEW_HALF;
    view.size   = PAX_VIEW_SIZE;
    view.unit   = PAX_TILE_SIZE;
    view.target = position(0).whole() + 0.5 - view.offset;

    // Prepares and fills the event dispat.
    dispat.acquire({32u, 8u});

    dispat.insert(&on_display_event, pax_self);
    dispat.insert(&on_keybd_event, pax_self);
    dispat.insert(&on_mouse_event, pax_self);

    // Prepares the display.
    display.acquire(monitor,
        PAX_TITLE, PAX_VIEW_SIZE * PAX_TILE_SIZE
    );

    // Prepares the painter.
    painter.acquire(display);
    painter.set_blend_mode(Blend_Mode::BLEND);

    // The state is active if and only if the display and the painter are both in a valid state.
    active = display.is_valid() &&
             painter.is_valid();

    // If the state should be inactive, releases every resource.
    if ( active == false )
        release();
}

void
Main_State::release()
{
    // Releases every resource in reverse order.
    painter.release();
    display.release();
    dispat.release();
    colour.release();
    movement.release();
    position.release();
    actors.release();
    ground.release();
}

bool
Main_State::input()
{
    while ( event_poll(dispat) )
        ;

    return active;
}

void
Main_State::fixed_step(f64 time)
{
    #if DEMO_SHOW_TEXT_GRID
        actors_show();
    #endif

    actors_control();
    actors_collide();
    actors_move(time);
}

void
Main_State::after_step()
{
    painter.clear();

    ground_paint();
    actors_paint();

    painter.paint();
}

void
Main_State::actors_show()
{
    static const char* const TEXT_FGRND[] = {
        "\x1b[90m",
        "\x1b[93m",
    };

    static const char* const TEXT_BGRND[] = {
        "\x1b[46m",
    };

    static const char* const TEXT_CLEAR = "\x1b[0m";

    v4f64 diff = view.bounds();
    v4u64 rect = view.cull(diff, {0, 0, actors.size(0), actors.size(1)});

    system("release");

    for ( u64 row = 0; row < actors.size(1); row += 1u ) {
        for ( u64 col = 0; col < actors.size(0); col += 1u ) {
            u64 index = actors(col, row);

            if ( col >= rect(0) && col < rect(2) &&
                 row >= rect(1) && row < rect(3) )
                printf("%s", TEXT_BGRND[0]);

            printf("%s%3lu%s ",
                TEXT_FGRND[index != 0], index, TEXT_CLEAR
            );
        }

        printf("\n");
    }

    printf("target = %.3lf, %.3lf\n", view.target(0), view.target(1));
    printf("offset = %.3lf, %.3lf\n", view.offset(0), view.offset(1));
    printf("scale  = %.3lf, %.3lf\n", view.scale(0), view.scale(1));
    printf("point  = %3lu, %3lu\n", position(0).point(0), position(0).point(1));
}

// todo: Use functions to fix this if-else.
void
actors_control_move(u64 index, Main_State*, Movement* movement)
{
    // Mobile but not moving.
    u64 flags = Movement::FLAGS_MOBILE;

    if ( movement->flags == flags ) {
        movement->input = {rand() % 3 - 1, rand() % 3 - 1};

        if ( index == 0 ) {
            movement->input(0) = (is_keybd_press(Keybd::D) || is_keybd_press(Keybd::RIGHT)) -
                                 (is_keybd_press(Keybd::A) || is_keybd_press(Keybd::LEFT));

            movement->input(1) = (is_keybd_press(Keybd::S) || is_keybd_press(Keybd::DOWN)) -
                                 (is_keybd_press(Keybd::W) || is_keybd_press(Keybd::UP));
        }
    }
}

void
Main_State::actors_control()
{
    for ( u64 i = 0; i < movement.size; i += 1u )
        actors_control_move(i, this, &movement(i));
}

void
actors_collide_borders(u64, Main_State* state, Position* position, Movement* movement)
{
    v2u64 tile = position->point;
    v2u64 next = tile + movement->input;

    if ( tile != next ) {
        for ( u64 i = 0; i < tile.SIZE; i += 1u ) {
            if ( next(i) >= state->actors.size(i) )
                movement->input(i) = 0;
        }
    }
}

void
actors_collide_objects(u64, Main_State* state, Position* position, Movement* movement)
{
    static const Store<v2u64, 3u> ANGLE_PARTS = {
        v2u64 {1u,  0},
        v2u64 { 0, 1u},
        v2u64 {1u, 1u},
    };

    v2u64 tile = position->point;
    v2u64 next = tile + movement->input;
    v2s64 part = {};

    if ( tile != next ) {
        for ( u64 i = 0; i < ANGLE_PARTS.SIZE; i += 1u ) {
            part = movement->input * ANGLE_PARTS(i);
            next = tile + part;

            if ( state->actors(next) != 0 )
                movement->input -= part;
        }
    }
}

void
Main_State::actors_collide()
{
    for ( u64 i = 0; i < movement.size; i += 1u ) {
        actors_collide_borders(i, this, &position(i), &movement(i));
        actors_collide_objects(i, this, &position(i), &movement(i));
    }
}

void
actors_move_start(u64 index, Main_State* state, Position* position, Movement* movement)
{
    v2u64 tile = position->point;
    v2u64 next = tile + movement->input;
    f64   norm = 0;

    if ( tile != next ) {
        if ( state->actors(next) == 0 ) {
            norm = movement->input.norm();

            movement->target = next;
            movement->speed  = movement->limit / norm;
            movement->angle  = movement->input;
            movement->set_moving(true);

            state->actors(next) = index + 1u;
            state->actors(tile) = 0;
        }
    }
}

void
actors_move_compl(u64, Main_State*, Position* position, Movement* movement, f64 time)
{
    // At least moving.
    u64 flags = Movement::FLAGS_MOVING;

    f64 displ = 0;
    f64 angle = 0;

    if ( movement->flags >= flags ) {
        for ( u64 i = 0; i < position->displ.SIZE; i += 1u ) {
            position->displ(i) +=
                movement->angle(i) * movement->speed * time;

            displ = math_abs(position->displ(i));
            angle = math_abs(movement->angle(i));

            if ( displ >= angle ) {
                position->point(i) = movement->target(i);
                position->displ(i) = 0;
            }
        }

        if ( position->point == movement->target )
            movement->set_moving(false);
    }
}

void
Main_State::actors_move(f64 time)
{
    for ( u64 i = 0; i < movement.size; i += 1u ) {
        actors_move_start(i, this, &position(i), &movement(i));
        actors_move_compl(i, this, &position(i), &movement(i), time);
    }

    // Follows the player.
    view.target = position(0).displ + position(0).point + 0.5
                - view.offset;
}

void
ground_paint_collect(v2u64 index, Main_State* state, v4f64 diff)
{
    Colour rgba = state->GROUND_COLOURS(state->ground(index));
    v4f64  tile = {0, 0, state->view.unit(0), state->view.unit(1)};

    tile(0) = tile(2) * (index(0) - diff(0));
    tile(1) = tile(3) * (index(1) - diff(1));

    state->painter.set_colour(rgba);
    state->painter.paint_rect_fill(tile);
}

void
Main_State::ground_paint()
{
    v4f64  diff = view.bounds();
    v4u64  rect = view.cull(diff, {0, 0, ground.size(0), ground.size(1)});

    for ( u64 row = rect(1); row < rect(3); row += 1u ) {
        for ( u64 col = rect(0); col < rect(2); col += 1u )
            ground_paint_collect({col, row}, this, diff);
    }

    painter.set_colour();
}

void
actors_paint_collect(v2u64 index, Main_State* state, v4f64 diff)
{
    Colour rgba  = {};
    v4f64  tile  = {0, 0, state->view.unit(0), state->view.unit(1)};
    u64    actor = state->actors(index) - 1u;

    if ( actor != MAX_U64 ) {
        rgba = state->colour(actor);

        tile(0) = tile(2) * (state->position(actor).whole()(0) - diff(0));
        tile(1) = tile(3) * (state->position(actor).whole()(1) - diff(1));

        state->painter.set_colour(rgba);
        state->painter.paint_rect_fill(tile);
    }
}

void
Main_State::actors_paint()
{
    v4f64  diff  = view.bounds();
    v4u64  rect  = view.cull(diff, {0, 0, ground.size(0), ground.size(1)});

    for ( u64 row = rect(1); row < rect(3); row += 1u ) {
        for ( u64 col = rect(0); col < rect(2); col += 1u )
            actors_paint_collect({col, row}, this, diff);
    }

    painter.set_colour();
}

#endif // DEMO_MAIN_STATE_HPP