#include <iostream>
#include <string>

#include "struct.h"
#include "menu.h"

using namespace std;

int const index = 10;
struct Football P[index] = {};

int main()
{
    int f;

    do {
        f = Menu(P,2);
    } while (f == 1);

    return 0;
}
