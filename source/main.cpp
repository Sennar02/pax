#include <light/Memory/import.hpp>

using namespace light;

int
main(int, const char*[])
{
    Buf<s8, 32u> memory = {};

    Bump_Alloc   alloc = Bump_Alloc(memory.data, memory.SIZE);
    Array2d<s32> array = Array2d<s32>(&alloc);

    printf("%lu, %p\n",
        alloc.size,
        alloc.data
    );

    array.create({2, 2});

    if ( array.size != 0 ) {
        for ( u64 i = 0; i < array.size; i += 1u )
            printf("%u\n", array[i]);
    }

    array[1000];

    printf("%u\n", array.destroy());
    printf("%lu\n", array.size);

    return 0;
}
