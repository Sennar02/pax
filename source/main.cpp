#include <light/Engine/import.hpp>

#include <time.h>  // time
#include <stdio.h> // printf

#include <SDL2/SDL.h>

using namespace light;

namespace sdl
{
    using Window   = SDL_Window;
    using Renderer = SDL_Renderer;
    using Event    = SDL_Event;
} // sdl

struct Title_State
    : public State
{
public:
    Title_State()
        : window {0}
        , renderer {0}
    {}

    void
    startup()
    {
        window = SDL_CreateWindow("Light",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            1536, 864, 0
        );

        if ( window != 0 ) {
            renderer = SDL_CreateRenderer(window, -1,
                SDL_RENDERER_ACCELERATED
            );

            if ( renderer == 0 ) {
                SDL_DestroyWindow(window);
                window = 0;
            }
        }

        printf("Window   = %p\n", window);
        printf("Renderer = %p\n", renderer);
    }

    void
    cleanup()
    {
        if ( window != 0 )
            SDL_DestroyWindow(window);

        if ( renderer != 0 )
            SDL_DestroyRenderer(renderer);
    }

    void enter() {}

    void leave() {}

    bool
    input()
    {
        sdl::Event event;

        while ( SDL_PollEvent(&event) != 0 ) {
            if ( event.type == SDL_QUIT ) return false;

            if ( event.type == SDL_KEYUP ) {
                if ( event.key.keysym.sym == SDLK_ESCAPE )
                    return false;
            }
        }

        return true;
    }

    void
    fixed_step(f32 step) {}

    void
    after_step()
    {
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

private:
    sdl::Window*   window;
    sdl::Renderer* renderer;
};

int
main(int, const char*[])
{
    Title_State title_state;
    Engine      engine;

    SDL_Init(SDL_INIT_VIDEO);

    engine.execute(&title_state, 80u);

    SDL_Quit();

    return 0;
}
