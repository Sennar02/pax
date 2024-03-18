#include <pax/Memory/import.hpp>

using namespace pax;

int
main(int, const char*[])
{
    Buf<s8, 256u> memory = {};

    Bump_Alloc      bump = Bump_Alloc::build(memory.data, memory.SIZE);
    Array_List<u32> list = Array_List<u32>::build(50, &bump);

    list.insert(1, list.count);
    list.insert(2, list.count);
    list.insert(3, list.count);

    printf("list = { ");

    for ( u64 i = 0; i < list.count; i += 1u )
        printf("%u ", list.array.data[i]);

    printf("}\n\n");

    while ( list.count != 0 ) {
        printf("list = { ");

        for ( u64 i = 0; i < list.count; i += 1u )
            printf("%u ", list.array.data[i]);

        printf("}\n -> ");

        Opt<u32> item = list.remove(0);

        if ( item.is_valid ) {
            printf("item = %u, ", item.item);
            printf("list = { ");

            for ( u64 i = 0; i < list.count; i += 1u )
                printf("%u ", list.array.data[i]);

            printf("}\n");
        }
    }

    return 0;
}
