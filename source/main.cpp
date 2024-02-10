#include <light/Base/import.hpp>

#include <time.h>  // time
#include <stdio.h> // printf

using namespace light;

int
main(int argc, const char* argv[])
{
    String arg;
    u32    cnt = 1u;

    srand(time(0));

    if ( argc == 2 ) {
        arg = String(argv[1], 0, MAX_U32);

        if ( arg.size != 0 )
            cnt = parse_int(arg);
    }

    for ( u32 i = 0; i < cnt; i += 1u )
        printf("%u\n", rand() % 100u);

    return 0;
}
