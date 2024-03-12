#include <pax/Memory/import.hpp>

using namespace pax;

int
main(int, const char*[])
{
    Buf<s8, 32u> memory = {};

    Bump_Alloc   alloc = Bump_Alloc(memory.data, memory.SIZE);
    Array2d<s32> array = Array2d<s32>();

    printf("%lu, %p\n",
        alloc.size,
        (void*) alloc.data
    );

    array.create({2, 2}, &alloc);

    if ( array.size != 0 ) {
        for ( u64 r = 0; r < array.rows; r += 1u ) {
            for ( u64 c = 0; c < array.cols; c += 1u )
                printf("%3u ", array[{r, c}]);

            printf("\n");
        }
    }

    // array[1000];

    printf("%u\n", array.destroy());
    printf("%lu\n", array.size);

    return 0;
}
