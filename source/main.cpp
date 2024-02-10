#include <light/Base/import.hpp>

#include <time.h>  // time
#include <stdio.h> // printf

using namespace light;

static const String STRING =
    String(
        "111011010111111 01100.110111001 110010100100001 011010111000100 01000.11001e001 11000111001100. 10.01100e000011 010.011101e0001 110011001101101 100010101.10e10",
        0, MAX_U32
    );

int
main(int, const char*[])
{
    String            string = STRING;
    Array<String, 2u> pieces;

    while ( string.size != 0 ) {
        pieces = string.split(' ');

        printf("[%.*s] -> [%.20f]\n",
            pieces[0].size, pieces[0].data,
            parse_flt(pieces[0])
        );

        string = pieces[1];
    }

    return 0;
}
