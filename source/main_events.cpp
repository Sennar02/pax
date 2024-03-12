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
    Dispatcher    dispatcher;
    System_Source system_src;
    Keybd_Printer keybd_printer;
    Mouse_Printer mouse_printer;
    Closer        closer;
    Display       display;
    Painter       painter;

    closer.display = &display;

    dispatcher.table = Array<void*>(
        calloc(1, sizeof(void*) * 10),
        sizeof(void*) * 10
    );

    dispatcher.insert(keybd_printer);
    dispatcher.insert<Display_Signal>(closer);
    dispatcher.insert<Keybd_Signal>(closer);
    dispatcher.insert(mouse_printer);

    Screen screen;

    SDL_Init(SDL_INIT_VIDEO);

    display.create(screen, screen.size(),
        String("Pax Tibi", 0, 10),
        Display::BORDERLESS | Display::ALWAYS_TOP
    );

    if ( display.is_valid() ) {
        painter.create(display);

        if ( painter.is_valid() == false )
            display.destroy();
    }

    while ( display.is_valid() ) {
        system_src.provide(dispatcher);

        painter.prepare();
        painter.present();
    }

    SDL_Quit();

    return 0;
}
