#include <pax/Engine/import.hpp>

using namespace pax;

struct App_Closer
    : public Observer<Keybd_Signal>
    , public Observer<Display_Signal>
{
public:
    bool status = true;

public:
    void
    receive(const Keybd_Signal& signal)
    {
        if ( signal.is_press() ) return;

        if ( signal.symbol == Keybd_Symb::ESC )
            status = false;
    }

    void
    receive(const Display_Signal& signal)
    {
        if ( signal.is_close() )
            status = false;
    }
};

struct Back_Grid
    : public Tile_Grid
{
public:
    void
    operate()
    {
        Array<u64> array;

        system("clear");

        for ( u64 r = 0; r < table.rows; r += 1u ) {
            array = table[r];

            for ( u64 c = 0; c < array.size; c += 1u )
                printf("%lu ", array[c]);

            printf("\n");
        }
    }
};

struct App
    : public State
{
public:
    Display    display = {};
    Painter    painter = {};
    Dispatcher dispat  = {};
    App_Closer closer  = {};
    Back_Grid  grid    = {};

public:
    App() { }

    void
    start()
    {
        Screen screen;

        display.create(screen, screen.size() / 2u,
            String("Pax", 0, 10u)
        );

        if ( display.is_valid() ) {
            painter.create(display);

            if ( painter.is_valid() == false )
                display.destroy();
        }

        dispat.table = Array2d<void*>(calloc(1u, LEN_UPTR * 64 * 64), {64, 64});
        grid.table = Array2d<u64>(calloc(1u, LEN_U64 * 96 * 32), {96, 32});

        dispat.insert<Keybd_Signal>(closer);
        dispat.insert<Display_Signal>(closer);
    }

    void
    clean()
    {
        painter.destroy();
        display.destroy();

        free(dispat.table.data);
    }

    void
    enter() {}

    void
    leave() {}

    bool
    input()
    {
        while ( system_src.provide(dispat) )
            ;

        return closer.status;
    }

    void
    fixed_step(f64, u64)
    {
        grid.operate();
    }

    void
    after_step()
    {
        painter.prepare();
        painter.present();
    }
};

int
main(int, char*[])
{
    App    a;
    Engine e;

    if ( SDL_Init(SDL_INIT_EVERYTHING) != 0 )
        return 1;

    e.execute(a, 192u);

    SDL_Quit();

    return 0;
}