#include <light/Base/import.hpp>
#include <stdio.h>

using namespace light;

int
main(int, const char*[])
{
    String view = String("\n\t    Some obscure\n\r\t Text   \n\r\t");

    view.trim();

    printf("[%.*s]\n",
        view.size,
        view.data);

    return 0;
}
