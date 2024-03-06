#include "Game_State.hpp"

namespace game
{
    using namespace light;

    static const u64        bump_size = 1024 * 256u;
    static       Bump_Alloc bump;

    static const String title = String("Light", 0, 5u);

    Game_State::Game_State(
        v2u64 grid_size,
        u64   grid_layers,
        u64   grid_steps,
        u64   tile_size,
        v2u64 view_size
    )
        : display {}
        , painter {}
        , grid {}
        , view {}
        , grid_size {grid_size}
        , tile_size {tile_size}
        , view_size {view_size}
    {
        Grid_Layer layer;

        bump = Bump_Alloc(calloc(1u, bump_size), bump_size);

        grid.layers = Array<Grid_Layer>(grid_layers, &bump);

        for ( u64 l = 0; l < grid.layers.size; l += 1u ) {
            layer.table = Array2d<u64>(grid_size, &bump);
            layer.steps = Array<Grid_Step*>(grid_steps, &bump);

            grid.push(layer);
        }

        view.size = view_size;
        view.unit = tile_size;
    }

    void
    Game_State::startup()
    {
        display.create(title, view_size * tile_size);

        if ( display.is_valid() ) {
            painter.create(display);

            if ( painter.is_valid() == false )
                display.destroy();
        }
    }

    void
    Game_State::cleanup()
    {
        painter.destroy();
        display.destroy();

        free(bump.data);
    }

    void
    Game_State::enter()
    {}

    void
    Game_State::leave()
    {}

    bool
    Game_State::input()
    {
        SDL_Event event;

        while ( SDL_PollEvent(&event) != 0 ) {
            if ( event.type == SDL_QUIT ) return false;

            if ( event.type == SDL_KEYUP ) {
                if ( event.key.keysym.sym == SDLK_ESCAPE )
                    return false;

                if ( event.key.keysym.sym == SDLK_z )
                    mult = 0.01;
            }

            if ( event.type == SDL_KEYDOWN ) {
                if ( event.key.keysym.sym == SDLK_z )
                    mult = 0.1;
            }

            if ( event.type == SDL_MOUSEWHEEL )
                view.factor += event.wheel.preciseY * mult;

            if ( event.type == SDL_MOUSEBUTTONDOWN ) {
                if ( event.button.button == SDL_BUTTON_MIDDLE )
                    view.factor = 1;
            }

            painter.scale(view.factor);
        }

        return true;
    }

    void
    Game_State::fixed_step(f64 time, u64 tick)
    {
        Grid_Layer layer;

        SDL_PumpEvents();

        for ( u64 l = 0; l < grid.count; l += 1u ) {
            layer = grid.layers[l];

            for ( u64 s = 0; s < layer.count; s += 1u )
                layer.steps[s]->fixed_step(time, layer.table);
        }

        if ( tick > 256u )
            light_panic("perf", "Falling behind %lu", tick);
    }

    void
    Game_State::after_step()
    {
        Grid_Layer layer;

        painter.prepare();

        for ( u64 l = 0; l < grid.count; l += 1u ) {
            layer = grid.layers[l];

            for ( u64 s = 0; s < layer.count; s += 1u )
                layer.steps[s]->after_step(layer.table);
        }

        painter.present();
    }
} // game
