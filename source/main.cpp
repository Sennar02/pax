#include <light/Base/import.hpp>

#include <time.h>  // time
#include <stdio.h> // printf

using namespace light;

int
main(int argc, const char* argv[])
{
    u32    count = 10u;
    String arg;

    if ( argc == 2 ) {
        arg = String(argv[1], 0, 5u);

        if ( arg.size != 0 )
            count = parse_int(arg);
    }

    srand(time(0));
/*
    for ( u32 i = 0; i < count; i += 1u )
        printf("[%5u] -> %u\n", i, rand() % 10u);
*/
    return 0;
}
