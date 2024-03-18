#include <pax/Engine/import.hpp>
#include <SDL2/SDL.h>

using namespace pax;

struct Keybd_Printer
    : public Observer<Keybd_Signal>
{
public:
    void
    receive(const Keybd_Signal& event)
    {
        system("clear");

        if ( event.is_release() )
            printf("release(%lu)\n", event.symbol);
        else
            printf("press(%lu)\n", event.symbol);
    }
};

struct Closer
    : public Observer<Keybd_Signal>
    , public Observer<Display_Signal>
{
public:
    Display* display = 0;

    void
    receive(const Keybd_Signal& event)
    {
        if ( event.is_press() ) return;

        if ( event.symbol == Keybd_Symb::ESC && display != 0 )
            display->destroy();
    }

    void
    receive(const Display_Signal& event)
    {
        if ( event.is_close() && display != 0 )
            display->destroy();
    }
};

struct Mouse_Printer
    : public Observer<Mouse_Signal>
{
public:
    void
    receive(const Mouse_Signal& mouse)
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
    Bump_Alloc bump = Bump_Alloc::build(
        calloc(1u, 1024u * 128u), 1024u * 128u
    );

    Dispatcher    dispat;
    System_Source system_src;
    Keybd_Printer keybd_printer;
    Mouse_Printer mouse_printer;
    Closer        closer;
    Display       display;
    Painter       painter;

    closer.display = &display;

    dispat = Dispatcher::build({10, 10}, &bump);

    printf("%lu\n", dispat.table.size);

    for ( u64 i = 0; i < dispat.table.size; i += 1u )
        printf("%lu\n", dispat.table[i].array.size);

    dispat.insert(keybd_printer);
    dispat.insert<Display_Signal>(closer);
    dispat.insert<Keybd_Signal>(closer);
    dispat.insert(mouse_printer);

    Screen screen;

    screen.index = 1;

    SDL_Init(SDL_INIT_VIDEO);

    display.create(screen, screen.size() / 2u,
        String::build("Pax Tibi", 0, 10)
    );

    if ( display.is_valid() ) {
        painter.create(display);

        if ( painter.is_valid() == false )
            display.destroy();
    }

    while ( display.is_valid() ) {
        system_src.provide(dispat);

        painter.prepare();
        painter.present();
    }

    SDL_Quit();

    return 0;
}
