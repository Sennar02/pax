#include <light/Base/import.hpp>

#include <time.h>  // time
#include <stdio.h> // printf

using namespace light;

int
main(int, const char*[])
{
    String string;
    f32    number = 0;

    string = {"-ab.5e-4b", 0, 10u};
    number = parse_flt(string, String::BASE_16, 16u);

    printf("%f\n", number);

    string = {"-ab.5e", 0, 10u};
    number = parse_flt(string, String::BASE_16, 16u);

    printf("%f\n", number);

    return 0;
}
