#include <light/Engine/import.hpp>
#include <SDL2/SDL.h>

using namespace light;

struct Keybd_Printer
    : public Observer<Keybd_Event>
{
public:
    void
    receive(const Keybd_Event& event)
    {
        system("clear");

        if ( event.is_release() )
            printf("release(%lu)\n", event.symbol);
        else
            printf("press(%lu)\n", event.symbol);
    }
};

struct Closer
    : public Observer<Keybd_Event>
{
public:
    Display* display = 0;

    void
    receive(const Keybd_Event& event)
    {
        if ( event.is_press() ) return;

        if ( event.symbol == SDLK_ESCAPE && display != 0 )
            display->destroy();
    }
};

struct Mouse_Printer
    : public Observer<Mouse_Event>
{
public:
    void
    receive(const Mouse_Event& mouse)
    {
        system("clear");

        printf(
            "%li (%li), %li (%li)\n"
            "%lf, %lf\n"
            "%lu | %lx\n",
            mouse.coords[0], mouse.motion[0],
            mouse.coords[1], mouse.motion[1],
            mouse.scroll[0], mouse.scroll[1],
            mouse.button, mouse.flags
        );
    }
};

int
main(int, const char*[])
{
    Event_Broker  broker;
    Event_Queue   queue;
    Keybd_Printer keybd_printer;
    Mouse_Printer mouse_printer;
    Closer        closer;
    Display       display;

    closer.display = &display;

    broker.table = Array<void*>(
        calloc(1, sizeof(void*) * 10),
        sizeof(void*) * 10
    );

    broker.insert(keybd_printer);
    broker.insert(closer);
    broker.insert(mouse_printer);

    display.create(String("Prova", 0, 10), {1280, 720});

    while ( display.is_valid() )
        queue.dequeue(broker);

    return 0;
}
