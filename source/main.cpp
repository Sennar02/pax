#include <light/Base/import.hpp>

#include <time.h>  // time
#include <stdio.h> // printf

namespace light
{
    namespace fails
    {
        enum Random {
            ZERO,
            SIZE,
        };

        static String RANDOM[Random::SIZE] = {
            String("[FAIL] Random: Extracted zero", 29u),
        };
    } // fails
} // light

using namespace light;

Res<f32, fails::Random>
random_0_to_1(f32 limit = 1.0f)
{
    using Random = fails::Random;

    Res<f32, Random> res = Res<f32, Random>(Random::ZERO);
    f32              val = rand() / (f32) RAND_MAX;

    if ( limit != 0  )
        res = Res<f32, Random>(val * limit);

    return res;
}

int
main(int, const char*[])
{
    srand( time(0) );

    printf("MAX_RAND = %u\n", RAND_MAX);

    for ( u32 i = 0 ; i < 10u; i += 1u ) {
        auto opt = random_0_to_1((f32) (rand() % 3u));

        if ( opt.full == false ) {
            printf("%.*s\n",
                fails::RANDOM[opt.fail].size,
                fails::RANDOM[opt.fail].data
            );
        } else
            printf("random = %.9f\n", opt.item);
    }

    return 0;
}
