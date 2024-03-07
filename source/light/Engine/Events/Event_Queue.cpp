#include <light/Engine/Events/Event_Queue.hpp>

namespace light
{
    void
    Event_Queue::dequeue(Event_Broker& broker)
    {
        SDL_Event event;

        while ( SDL_PollEvent(&event) != 0 ) {
            switch ( event.type ) {
                case SDL_KEYDOWN:         light_excl( broker.publish(from_sdl(event.key));    );
                case SDL_KEYUP:           light_excl( broker.publish(from_sdl(event.key));    );
                case SDL_MOUSEMOTION:     light_excl( broker.publish(from_sdl(event.motion)); );
                case SDL_MOUSEBUTTONDOWN: light_excl( broker.publish(from_sdl(event.button)); );
                case SDL_MOUSEBUTTONUP:   light_excl( broker.publish(from_sdl(event.button)); );
                case SDL_MOUSEWHEEL:      light_excl( broker.publish(from_sdl(event.wheel));  );
            }
        }
    }
} // light
