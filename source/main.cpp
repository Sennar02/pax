#include <light/Memory/import.hpp>

using namespace light;

int
main(int, const char*[])
{
    Buf<s8, 32u> memory = {};

    Pool_Alloc alloc = Pool_Alloc(memory.data, memory.SIZE, 16u, 8u);
    Array<s32> array = Array<s32>(&alloc);

    printf("%lu, %lu, %p\n",
        alloc.size,
        alloc.page,
        alloc.data
    );

    array.create(alloc.page / array.LEN_TYPE);

    if ( array.size != 0 ) {
        for ( u64 i = 0; i < array.size; i += 1u )
            printf("%u\n", array[i]);
    }

    printf("%u\n", array.destroy());
    printf("%lu\n", array.size);

    return 0;
}
