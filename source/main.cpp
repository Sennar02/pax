#include <light/Base/import.hpp>

#include <time.h>  // time
#include <stdio.h> // printf

using namespace light;

Opt<f32>
random_0_to_1(f32 limit = 1.0f)
{
    f32      val = rand() / (f32) RAND_MAX;
    Opt<f32> res;

    if ( limit != 0  )
        res = Opt<f32>(val * limit);

    return res;
}

int
main(int, const char*[])
{
    srand( time(0) );

    printf("MAX_RAND = %u\n", RAND_MAX);

    for ( u32 i = 0 ; i < 10u; i += 1u ) {
        auto opt = random_0_to_1(0.0f);

        if ( opt.full )
            printf("random = %.9f\n", opt.item);
        else
            printf("random = <fail>\n");
    }

    return 0;
}
